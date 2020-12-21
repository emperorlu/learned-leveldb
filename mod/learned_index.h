//
// Created by daiyi on 2020/02/02.
//

#ifndef LEVELDB_LEARNED_INDEX_H
#define LEVELDB_LEARNED_INDEX_H


#include <vector>
#include <cstring>
#include "util.h"
#include <atomic>
#include "plr.h"



using std::string;
using leveldb::Slice;
using leveldb::Version;
using leveldb::FileMetaData;



namespace adgMod {

    class LearnedIndexData;

    class AccumulatedNumEntriesArray {
        friend class LearnedIndexData;

    public:
        std::vector<std::pair<uint64_t, string>> array;
    public:
        AccumulatedNumEntriesArray() = default;
        void Add(uint64_t num_entries, string&& key);
        bool Search(const Slice& key, uint64_t lower, uint64_t upper, size_t* index, uint64_t* relative_lower, uint64_t* relative_upper);
        bool SearchNoError(uint64_t position, size_t* index, uint64_t* relative_position);
        uint64_t NumEntries() const;
    };


    class VersionAndSelf {
    public:
        Version* version;
        int v_count;
        LearnedIndexData* self;
        int level;
    };

    class MetaAndSelf {
    public:
        Version* version;
        int v_count;
        FileMetaData* meta;
        LearnedIndexData* self;
        int level;
    };
    class LearnedIndexData {
        friend class leveldb::Version;
        friend class leveldb::VersionSet;
    private:
        double error;
        std::atomic<bool> learned;
        std::atomic<bool> aborted;
        bool learned_not_atomic;
        std::atomic<bool> learning;
        int allowed_seek;
        int current_seek;
    public:
        bool filled;
        bool is_level;

        std::vector<Segment> string_segments;
        uint64_t min_key;
        uint64_t max_key;
        uint64_t size;



    public:
        std::vector<std::string> string_keys;
        AccumulatedNumEntriesArray num_entries_accumulated;

        int level;
        mutable int served;
        uint64_t cost;

//        int num_neg_model = 0, num_pos_model = 0, num_neg_baseline = 0, num_pos_baseline = 0;
//        uint64_t time_neg_model = 0, time_pos_model = 0, time_neg_baseline = 0, time_pos_baseline = 0;
//
//        int num_neg_model_p = 0, num_pos_model_p = 0, num_neg_baseline_p = 0, num_pos_baseline_p = 0, num_files_p = 0;
//        uint64_t time_neg_model_p = 0, time_pos_model_p = 0, time_neg_baseline_p = 0, time_pos_baseline_p = 0;
//        double gain_p = 0;
//        uint64_t file_size = 0;




        explicit LearnedIndexData(int allowed_seek) : error(adgMod::model_error), learned(false), aborted(false), learning(false),
            learned_not_atomic(false), allowed_seek(allowed_seek), current_seek(0), filled(false), is_level(false), level(0), served(0), cost(0) {};
        LearnedIndexData(const LearnedIndexData& other) = delete;
        std::pair<uint64_t, uint64_t> GetPosition(const Slice& key) const;
        uint64_t MaxPosition() const;
        double GetError() const;
        bool Learn();
        bool Learned();
        bool Learned(Version* version, int v_count, int level);
        bool Learned(Version* version, int v_count, FileMetaData* meta, int level);
        static void Learn(void* arg);
        static uint64_t FileLearn(void* arg);
        bool FillData(Version* version, FileMetaData* meta);
        void WriteModel(const string& filename);
        void ReadModel(const string& filename);
        void ReportStats();
        void FillCBAStat(bool positive, bool model, uint64_t time);
    };


    class FileLearnedIndexData {
    private:
        leveldb::port::Mutex mutex;
        std::vector<LearnedIndexData*> file_learned_index_data;
    public:
        uint64_t watermark;


        bool Learned(Version* version, FileMetaData* meta, int level);
        bool FillData(Version* version, FileMetaData* meta);
        std::vector<std::string>& GetData(FileMetaData* meta);
        std::pair<uint64_t, uint64_t> GetPosition(const Slice& key, int file_num);
        AccumulatedNumEntriesArray* GetAccumulatedArray(int file_num);
        LearnedIndexData* GetModel(int number);
        void Report();
        ~FileLearnedIndexData();
    };

}

#endif //LEVELDB_LEARNED_INDEX_H
