#include <cassert>
#include <chrono>
#include <iostream>
#include "leveldb/db.h"
#include "leveldb/comparator.h"
#include "util.h"
#include "stats.h"
#include "learned_index.h"
#include <cstring>
#include "cxxopts.hpp"
#include <unistd.h>
#include <fstream>
#include "../db/version_set.h"
#include <cmath>
#include <random>

using namespace leveldb;
using namespace adgMod;
using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::vector;
using std::map;
using std::ifstream;
using std::string;

int num_pairs_base = 1000;
int mix_base = 20;
int chunk_size = 100000;



class NumericalComparator : public Comparator {
public:
    NumericalComparator() = default;
    virtual const char* Name() const {return "adgMod:NumericalComparator";}
    virtual int Compare(const Slice& a, const Slice& b) const {
        uint64_t ia = adgMod::ExtractInteger(a.data(), a.size());
        uint64_t ib = adgMod::ExtractInteger(b.data(), b.size());
        if (ia < ib) return -1;
        else if (ia == ib) return 0;
        else return 1;
    }
    virtual void FindShortestSeparator(std::string* start, const Slice& limit) const { return; };
    virtual void FindShortSuccessor(std::string* key) const { return; };
};


void PutAndPrefetch(int lower, int higher, vector<string>& keys) {
    adgMod::Stats* instance = adgMod::Stats::GetInstance();

    Status status;

    instance->StartTimer(9);
    for (int i = lower; i < higher; ++i) {
        string value = generate_value(0);
        status = db->Put(write_options, keys[i], value);
        assert(status.ok() && "File Put Error");
    }
    instance->PauseTimer(9, true);

    //cout << "Put Complete" << endl;


    instance->StartTimer(10);
    for (int i = lower; i < higher; ++i) {
        string value;
        status = db->Get(read_options, keys[i], &value);
        //cout << "Get " << keys[i] << " Done" << endl;
        assert(status.ok() && "File Get Error");
    }
    instance->PauseTimer(10, true);

    //cout << "Prefetch Complete" << endl;
};

enum LoadType {
    Ordered = 0,
    Reversed = 1,
    ReversedChunk = 2,
    Random = 3,
    RandomChunk = 4
};

int main(int argc, char *argv[]) {
    cout << "Run begin" << endl;
    int num_operations, num_iteration, num_mix;
    float test_num_segments_base;
    float num_pair_step;
    string db_location, profiler_out, input_filename, distribution_filename, ycsb_filename;
    bool print_single_timing, print_file_info, evict, unlimit_fd, use_distribution = false, pause, use_ycsb = false;
    bool change_level_load, change_file_load, change_level_learning, change_file_learning;
    int load_type, insert_bound, length_range;
    string db_location_copy;
    
    cout << "[Debug] run first" << endl;
    cxxopts::Options commandline_options("leveldb read test", "Testing leveldb read performance.");
    cout << "[Debug] run second" << endl;
    commandline_options.add_options()
            ("n,get_number", "the number of gets (to be multiplied by 1024)", cxxopts::value<int>(num_operations)->default_value("1000"))
            ("s,step", "the step of the loop of the size of db", cxxopts::value<float>(num_pair_step)->default_value("1"))
            ("i,iteration", "the number of iterations of a same size", cxxopts::value<int>(num_iteration)->default_value("1"))
            ("m,modification", "if set, run our modified version", cxxopts::value<int>(adgMod::MOD)->default_value("0"))
            ("h,help", "print help message", cxxopts::value<bool>()->default_value("false"))
            ("d,directory", "the directory of db", cxxopts::value<string>(db_location)->default_value("/mnt/ssd/testdb"))
            ("k,key_size", "the size of key", cxxopts::value<int>(adgMod::key_size)->default_value("8"))
            ("v,value_size", "the size of value", cxxopts::value<int>(adgMod::value_size)->default_value("8"))
            ("single_timing", "print the time of every single get", cxxopts::value<bool>(print_single_timing)->default_value("false"))
            ("file_info", "print the file structure info", cxxopts::value<bool>(print_file_info)->default_value("false"))
            ("test_num_segments", "test: number of segments per level", cxxopts::value<float>(test_num_segments_base)->default_value("1"))
            ("string_mode", "test: use string or int in model", cxxopts::value<bool>(adgMod::string_mode)->default_value("false"))
            ("e,model_error", "error in modesl", cxxopts::value<uint32_t>(adgMod::model_error)->default_value("8"))
            ("f,input_file", "the filename of input file", cxxopts::value<string>(input_filename)->default_value(""))
            ("multiple", "test: use larger keys", cxxopts::value<uint64_t>(adgMod::key_multiple)->default_value("1"))
            ("w,write", "writedb", cxxopts::value<bool>(fresh_write)->default_value("false"))
            ("c,uncache", "evict cache", cxxopts::value<bool>(evict)->default_value("false"))
            ("u,unlimit_fd", "unlimit fd", cxxopts::value<bool>(unlimit_fd)->default_value("false"))
            ("x,dummy", "dummy option")
            ("l,load_type", "load type", cxxopts::value<int>(load_type)->default_value("0"))
            ("filter", "use filter", cxxopts::value<bool>(adgMod::use_filter)->default_value("false"))
            ("mix", "mix read and write", cxxopts::value<int>(num_mix)->default_value("0"))
            ("distribution", "operation distribution", cxxopts::value<string>(distribution_filename)->default_value(""))
            ("change_level_load", "load level model", cxxopts::value<bool>(change_level_load)->default_value("false"))
            ("change_file_load", "enable level learning", cxxopts::value<bool>(change_file_load)->default_value("false"))
            ("change_level_learning", "load file model", cxxopts::value<bool>(change_level_learning)->default_value("false"))
            ("change_file_learning", "enable file learning", cxxopts::value<bool>(change_file_learning)->default_value("false"))
            ("p,pause", "pause between operation", cxxopts::value<bool>(pause)->default_value("false"))
            ("policy", "learn policy", cxxopts::value<int>(adgMod::policy)->default_value("0"))
            ("YCSB", "use YCSB trace", cxxopts::value<string>(ycsb_filename)->default_value(""))
            ("insert", "insert new value", cxxopts::value<int>(insert_bound)->default_value("0"))
            ("range", "use range query and specify length", cxxopts::value<int>(length_range)->default_value("0"));
    auto result = commandline_options.parse(argc, argv);
    if (result.count("help")) {
        printf("%s", commandline_options.help().c_str());
        exit(0);
    }
    //cout << "[Debug] run 1" << endl;
    std::default_random_engine e1(0), e2(255), e3(0);
    srand(0);
    num_operations *= num_pairs_base;
    db_location_copy = db_location;

    adgMod::fd_limit = unlimit_fd ? 1024 * 1024 : 1024;
    adgMod::restart_read = true;
    adgMod::level_learning_enabled ^= change_level_learning;
    adgMod::file_learning_enabled ^= change_file_learning;
    adgMod::load_level_model ^= change_level_load;
    adgMod::load_file_model ^= change_file_load;
    //cout << "[Debug] run 2" << endl;
   // adgMod::file_learning_enabled = false;


    vector<string> keys;
    vector<uint64_t> distribution;
    vector<int> ycsb_is_write;
    //keys.reserve(100000000000 / adgMod::value_size);
    if (!input_filename.empty()) {
        ifstream input(input_filename);
        string key;
        while (input >> key) {
            if(key.length() <= key_size ){
                //string the_key = generate_key(key);
                //keys.push_back(std::move(the_key));
                keys.push_back(std::move(key));
            }
            // string the_key = generate_key(key);
            // keys.push_back(std::move(the_key));
        }
        //adgMod::key_size = (int) keys.front().size();
    } else {
        std::uniform_int_distribution<uint64_t> udist_key(0, 999999999999999);
        for (int i = 0; i < 10000000; ++i) {
            keys.push_back(generate_key(to_string(udist_key(e2))));
        }
    }
    if (!distribution_filename.empty()) {
        use_distribution = true;
        ifstream input(distribution_filename);
        uint64_t index;
        while (input >> index) {
            distribution.push_back(index);
        }
    }

    if (!ycsb_filename.empty()) {
        use_ycsb = true;
        use_distribution = true;
        ifstream input(ycsb_filename);
        uint64_t index;
        int is_write;
        while (input >> is_write >> index) {
            distribution.push_back(index);
            ycsb_is_write.push_back(is_write);
        }
    }
    bool copy_out = num_mix != 0 || use_ycsb;

    adgMod::Stats* instance = adgMod::Stats::GetInstance();
    vector<vector<size_t>> times(20);
    string values(1024 * 1024, '0');

    if (copy_out) {
        system("sync; echo 3 | sudo tee /proc/sys/vm/drop_caches");
    }

    if (num_mix > 1000) {
        mix_base = 1000;
        num_mix -= 1000;
    }
    
    for (size_t iteration = 0; iteration < num_iteration; ++iteration) {
        if (copy_out) {
            system("sudo fstrim -a -v");
        }

        db_location = db_location_copy;
        std::uniform_int_distribution<uint64_t > uniform_dist_file(0, (uint64_t) keys.size() - 1);
        std::uniform_int_distribution<uint64_t > uniform_dist_file2(0, (uint64_t) keys.size() - 1);
        std::uniform_int_distribution<uint64_t > uniform_dist_value(0, (uint64_t) values.size() - adgMod::value_size - 1);

        DB* db;
        Options options;
        ReadOptions& read_options = adgMod::read_options;
        WriteOptions& write_options = adgMod::write_options;
        Status status;

        options.create_if_missing = true;
        //options.comparator = new NumericalComparator;
        //adgMod::block_restart_interval = options.block_restart_interval = adgMod::MOD == 8 || adgMod::MOD == 7 ? 1 : adgMod::block_restart_interval;
        //read_options.fill_cache = true;
        write_options.sync = false;
        instance->ResetAll();

        // cout << "[Debug] keys.size(): " << keys.size() << endl;
        // for (int i = 0; i < keys.size(); ++i){
        //     cout << "[Debug] keys." << i << ": " << keys[i] << endl;
        // }

        if (fresh_write && iteration == 0) {
            string command = "rm -rf " + db_location;
            system(command.c_str());
            system("sudo fstrim -a -v");
            system("sync; echo 3 | sudo tee /proc/sys/vm/drop_caches");
            cout << "delete and trim complete" << endl;

            status = DB::Open(options, db_location, &db);
            assert(status.ok() && "Open Error");


            instance->StartTimer(9);
            int cut_size = keys.size() / chunk_size;
            if (cut_size == 0) cut_size = 1; 
            std::vector<std::pair<int, int>> chunks;
            // cout << "[Debug]load_type: " << load_type << endl;
            switch (load_type) {
                case Ordered: {
                    for (int cut = 0; cut < cut_size; ++cut) {
                        chunks.emplace_back(keys.size() * cut / cut_size, keys.size() * (cut + 1) / cut_size);
                    }
                    break;
                }
                case ReversedChunk: {
                    for (int cut = cut_size - 1; cut >= 0; --cut) {
                        chunks.emplace_back(keys.size() * cut / cut_size, keys.size() * (cut + 1) / cut_size);
                    }
                    break;
                }
                case Random: {
                    std::random_shuffle(keys.begin(), keys.end());
                    for (int cut = 0; cut < cut_size; ++cut) {
                        chunks.emplace_back(keys.size() * cut / cut_size, keys.size() * (cut + 1) / cut_size);
                    }
                    break;
                }
                case RandomChunk: {
                    for (int cut = 0; cut < cut_size; ++cut) {
                        chunks.emplace_back(keys.size() * cut / cut_size, keys.size() * (cut + 1) / cut_size);
                    }
                    std::random_shuffle(chunks.begin(), chunks.end());
                    break;
                }
                default: assert(false && "Unsupported load type.");
            }

            // cout << "[Debug]begin put" << endl;
            for (int cut = 0; cut < chunks.size(); ++cut) {
                for (int i = chunks[cut].first; i < chunks[cut].second; ++i) {
                    status = db->Put(write_options, keys[i], {values.data() + uniform_dist_value(e2), (uint64_t) adgMod::value_size});
                    assert(status.ok() && "File Put Error");
                }
            }
            adgMod::db->vlog->Sync();
            instance->PauseTimer(9, true);
            cout << "Put Complete" << endl;

            keys.clear();
            
            //print_file_info
            if (print_file_info && iteration == 0) db->PrintFileInfo(); 

            //WaitForBackground
            adgMod::db->WaitForBackground();
            delete db;

            cout << "[Debug] Open db to learn" << endl;
            status = DB::Open(options, db_location, &db);
            adgMod::db->WaitForBackground();

            //Use Mod
            if (adgMod::MOD == 6 || adgMod::MOD == 7) {
                Version* current = adgMod::db->versions_->current();
                for (int i = 1; i < config::kNumLevels; ++i) {
                    cout << "[Debug]learn mod" << endl;
                    LearnedIndexData::Learn(new VersionAndSelf{current, adgMod::db->version_count, current->learned_index_data_[i].get(), i});
                }
                current->FileLearn();
            }
            cout << "Shutting down" << endl;
            adgMod::db->WaitForBackground();
            //delete db;

            //keys.reserve(100000000000 / adgMod::value_size);
            if (!input_filename.empty()) {
                ifstream input(input_filename);
                string key;
                while (input >> key) {
                    if(key.length() <= key_size ){
                        //string the_key = generate_key(key);
                        //keys.push_back(std::move(the_key));
                        keys.push_back(std::move(key));
                    }
                    // string the_key = generate_key(key);
                    // keys.push_back(std::move(the_key));
                }
                adgMod::key_size = (int) keys.front().size();
            }
            fresh_write = false;
        }



        if (copy_out) {
            string db_location_mix = db_location + "_mix";
            string remove_command = "rm -rf " + db_location_mix;
            string copy_command = "cp -r " + db_location + " " + db_location_mix;

            system(remove_command.c_str());
            system(copy_command.c_str());
            db_location = db_location_mix;
        }




        if (evict) system("sync; echo 3 | sudo tee /proc/sys/vm/drop_caches");

        cout << "Starting up" << endl;
        //status = DB::Open(options, db_location, &db);
        cout << "[Debug] open db to find" << endl;
        adgMod::db->WaitForBackground();

        Iterator* db_iter = length_range == 0 ? nullptr : db->NewIterator(read_options);
        assert(status.ok() && "Open Error");
        //            for (int s = 12; s < 20; ++s) {
        //                instance->ResetTimer(s);
        //            }

        //        if (adgMod::MOD == 6 || adgMod::MOD == 7) {
        //            for (int i = 1; i < config::kNumLevels; ++i) {
        //                Version* current = adgMod::db->versions_->current();
        //                LearnedIndexData::Learn(new VersionAndSelf{current, adgMod::db->version_count, current->learned_index_data_[i].get(), i});
        //            }
        //        }
        //        cout << "Shutting down" << endl;
        //        adgMod::db->WaitForBackground();
        //        delete db;
        //        return 0;

        uint64_t last_read = 0, last_write = 0;
        int last_level = 0, last_file = 0, last_baseline = 0, last_succeeded = 0, last_false = 0, last_compaction = 0, last_learn = 0;
        std::vector<uint64_t> detailed_times;
        bool start_new_event = true;

        instance->StartTimer(13);
        uint64_t write_i = 0;
        for (int i = 0; i < num_operations; ++i) {

            if (start_new_event) {
                detailed_times.push_back(instance->GetTime());
                start_new_event = false;
            }

            bool write = use_ycsb ? ycsb_is_write[i] == 1 || ycsb_is_write[i] == 2 : (i % mix_base) < num_mix;
            length_range = use_ycsb && ycsb_is_write[i] > 2 ? ycsb_is_write[i] - 100 : length_range;

            if (write) {
                cout << "Write begin" << endl;
                if (input_filename.empty()) {
                    instance->StartTimer(10);
                    status = db->Put(write_options, generate_key(to_string(distribution[i])), {values.data() + uniform_dist_value(e3), (uint64_t) adgMod::value_size});
                    instance->PauseTimer(10);
                } else {
                    uint64_t index;
                    if (use_distribution) {
                        index = distribution[i];
                    } else if (load_type == 0) {
                        index = write_i++ % keys.size();
                    } else {
                        index = uniform_dist_file(e1) % (keys.size() - 1);
                    }

                    instance->StartTimer(10);
                    if (use_ycsb && ycsb_is_write[i] == 2) {
                        status = db->Put(write_options, generate_key(to_string(10000000000 + index)), {values.data() + uniform_dist_value(e3), (uint64_t) adgMod::value_size});
                    } else {
                        status = db->Put(write_options, keys[index], {values.data() + uniform_dist_value(e3), (uint64_t) adgMod::value_size});
                    }
                    instance->PauseTimer(10);
                    assert(status.ok() && "Mix Put Error");
                    //cout << index << endl;
                }
            } else if (length_range != 0) {
                cout << "Seek begin" << endl;
                // Seek
                if (input_filename.empty()) {
                    instance->StartTimer(4);
                    db_iter->Seek(generate_key(to_string(distribution[i])));
                    instance->PauseTimer(4);
                } else {
                    uint64_t index = use_distribution ? distribution[i] : uniform_dist_file2(e2) % (keys.size() - 1);
                    index = index >= length_range ? index - length_range : 0;
                    const string& key = keys[index];
                    instance->StartTimer(4);
                    db_iter->Seek(key);
                    instance->PauseTimer(4);
                }
                
                cout << "Range begin" << endl;
                // Range
                instance->StartTimer(17);
                for (int r = 0; r < length_range; ++r) {
                    if (!db_iter->Valid()) break;
                    Slice key = db_iter->key();
                    string value = db_iter->value().ToString();
                    // cout << key.ToString() << value << endl;
                    // value.clear();
                    db_iter->Next();
                }
                instance->PauseTimer(17);
            } else {
                //cout << "[Debug] find begin" << endl;
                string value;
                if (input_filename.empty()) {
                    instance->StartTimer(4);
                    status = db->Get(read_options, generate_key(to_string(distribution[i])), &value);
                    instance->PauseTimer(4);
                    if (!status.ok()) {
                        // cout << "[Not Found 1] ";
                        cout << distribution[i] << " Not Found" << endl;
                        //assert(status.ok() && "File Get Error");
                    }
                } else {
                    uint64_t index = use_distribution ? distribution[i] : uniform_dist_file2(e2) % (keys.size() - 1);
                    const string& key = keys[index];
                    instance->StartTimer(4);
                    if (insert_bound != 0 && index > insert_bound) {
                        status = db->Get(read_options, generate_key(to_string(10000000000 + index)), &value);
                    } else {
                        //cout << "[Debug] db->Get begin" << endl;
                        //cout << "[Get] " << key  << endl;
                        status = db->Get(read_options, key, &value);
                        
                    }
                    instance->PauseTimer(4);

                    //cout << "[Get] " << key << " : " << value << endl;
                    if (!status.ok()) {
                        // cout << "[Not Found 2] ";
                        cout << key << " Not Found" << endl;
                        //assert(status.ok() && "File Get Error");
                    }
                }
            }

            // cout << "[Debug] Over" << endl;

            if (pause) {
                if ((i + 1) % (num_operations / 10000) == 0) ::usleep(800000);
            }

            if ((i + 1) % (num_operations / 100) == 0) detailed_times.push_back(instance->GetTime());
            if ((i + 1) % (num_operations / 10) == 0) {
                int level_read = levelled_counters[0].Sum();
                int file_read = levelled_counters[1].Sum();
                int baseline_read = levelled_counters[2].Sum();
                int succeeded_read = levelled_counters[3].NumSum();
                int false_read = levelled_counters[4].NumSum();

                compaction_counter_mutex.Lock();
                int num_compaction = events[0].size();
                compaction_counter_mutex.Unlock();
                learn_counter_mutex.Lock();
                int num_learn = events[1].size();
                learn_counter_mutex.Unlock();

                uint64_t read_time = instance->ReportTime(4);
                uint64_t write_time = instance->ReportTime(10);
                std::pair<uint64_t, uint64_t> time = {detailed_times.front(), detailed_times.back()};

                events[2].push_back(new WorkloadEvent(time, level_read - last_level, file_read - last_file, baseline_read - last_baseline,
                    succeeded_read - last_succeeded, false_read - last_false, num_compaction - last_compaction, num_learn - last_learn,
                    read_time - last_read, write_time - last_write, std::move(detailed_times)));

                last_level = level_read;
                last_file = file_read;
                last_baseline = baseline_read;
                last_succeeded = succeeded_read;
                last_false = false_read;
                last_compaction = num_compaction;
                last_learn = num_learn;
                last_read = read_time;
                last_write = write_time;
                detailed_times.clear();
                start_new_event = true;
                cout << (i + 1) / (num_operations / 10) << endl;
                Version* current = adgMod::db->versions_->current();
                printf("LevelSize %d %d %d %d %d %d\n", current->NumFiles(0), current->NumFiles(1), current->NumFiles(2), current->NumFiles(3),
                       current->NumFiles(4), current->NumFiles(5));
            }

        }
        instance->PauseTimer(13, true);



        instance->ReportTime();
        for (int s = 0; s < times.size(); ++s) {
            times[s].push_back(instance->ReportTime(s));
        }
        adgMod::db->WaitForBackground();
        sleep(10);



        for (auto& event_array : events) {
            for (Event* e : event_array) e->Report();
        }

        for (Counter& c : levelled_counters) c.Report();

        file_data->Report();

        for (auto it : file_stats) {
            printf("FileStats %d %d %lu %lu %u %u %lu %d\n", it.first, it.second.level, it.second.start,
                it.second.end, it.second.num_lookup_pos, it.second.num_lookup_neg, it.second.size, it.first < file_data->watermark ? 0 : 1);
        }

        adgMod::learn_cb_model->Report();

        delete db_iter;
        delete db;
    }


    for (int s = 0; s < times.size(); ++s) {
        vector<uint64_t>& time = times[s];
        vector<double> diff(time.size());
        if (time.empty()) continue;

        double sum = std::accumulate(time.begin(), time.end(), 0.0);
        double mean = sum / time.size();
        std::transform(time.begin(), time.end(), diff.begin(), [mean] (double x) { return x - mean; });
        double stdev = std::sqrt(std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0) / time.size());

        printf("Timer %d MEAN: %lu, STDDEV: %f\n", s, (uint64_t) mean, stdev);
    }

    if (num_iteration > 1) {
        cout << "Data Without the First Item" << endl;
        for (int s = 0; s < times.size(); ++s) {
            vector<uint64_t>& time = times[s];
            vector<double> diff(time.size() - 1);
            if (time.empty()) continue;

            double sum = std::accumulate(time.begin() + 1, time.end(), 0.0);
            double mean = sum / (time.size() - 1);
            std::transform(time.begin() + 1, time.end(), diff.begin(), [mean] (double x) { return x - mean; });
            double stdev = std::sqrt(std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0) / time.size());

            printf("Timer %d MEAN: %lu, STDDEV: %f\n", s, (uint64_t) mean, stdev);
        }
    }
}

