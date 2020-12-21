#include "leveldb/iterator.h"
#include "mod/learned_index.h"
#include "mod/stats.h"
#include "table/block.h"


namespace leveldb {

class LearnedIterator : public Iterator {
 public:
  LearnedIterator(Table* table, RandomAccessFile* file, adgMod::LearnedIndexData* file_model) :
		table(table), file(file), file_model(file_model),
    num_blocks(table->rep_->index_block->NumRestarts()),
    last_block_num_entries(file_model->MaxPosition() + 1 - (num_blocks - 1) * adgMod::block_num_entries),
    block_content(), current_block(-1), current_entry(-1), key_(), value_() { };

  virtual ~LearnedIterator() = default;

  virtual void Seek(const Slice& target) {
		adgMod::Stats* instance = adgMod::Stats::GetInstance();

		// read the model
		ParsedInternalKey parsed_key;
    ParseInternalKey(target, &parsed_key);
		auto bounds = file_model->GetPosition(parsed_key.user_key);
		uint64_t lower = bounds.first;
		uint64_t upper = bounds.second;
    
    // Not found in this file
		if (lower > file_model->MaxPosition()) {
      block_content.clear();
      current_block = -1;
      return;
    }

		// Get the position we want to read
		size_t index_lower = lower / adgMod::block_num_entries;
		size_t index_upper = upper / adgMod::block_num_entries;
		uint64_t i = index_lower;
    if (index_lower != index_upper) {
			Block* index_block = table->rep_->index_block;
      uint32_t mid_index_entry = DecodeFixed32(index_block->data_ + index_block->restart_offset_ + index_lower * sizeof(uint32_t));
      uint32_t shared, non_shared, value_length;
      const char* key_ptr = DecodeEntry(index_block->data_ + mid_index_entry,
                                        index_block->data_ + index_block->restart_offset_, &shared, &non_shared, &value_length);
      assert(key_ptr != nullptr && shared == 0 && "Index Entry Corruption");
      Slice mid_key(key_ptr, non_shared);
      int comp = table->rep_->options.comparator->Compare(mid_key, target);
      i = comp < 0 ? index_upper : index_lower;
    }

		// No filter block search, just read corresponding entries
		uint64_t left = i == index_lower ? lower % adgMod::block_num_entries : 0;
    uint64_t right = i == index_upper ? upper % adgMod::block_num_entries : adgMod::block_num_entries - 1;
    if (current_block != i) {
      current_block = i;
      ReadDataBlock();
    }

    assert(!block_content.empty());
		// Binary Search
    while (left < right) {
      uint32_t mid = (left + right) / 2;
      uint32_t shared, non_shared, value_length;
      const char* key_ptr = DecodeEntry(block_content.data() + mid * adgMod::entry_size,
              block_content.data() + adgMod::block_size, &shared, &non_shared, &value_length);
      assert(key_ptr != nullptr && shared == 0 && "Entry Corruption");
      Slice mid_key(key_ptr, non_shared);
      int comp = table->rep_->options.comparator->Compare(mid_key, target);
      if (comp < 0) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }

		// Set appropriate values
    current_block = i;
    current_entry = left;
    ParseEntry();
	}

  virtual void SeekToFirst() { 
    current_block = 0;
    current_entry = 0;
    ReadDataBlock();
    ParseEntry();
  }

  virtual void SeekToLast() { assert(false); }
  virtual void Prev() { assert(false); }

  virtual void Next() { 
    ++current_entry;
    if (current_block == num_blocks - 1) {
      if (current_entry >= last_block_num_entries) {
        block_content.clear();
        current_block = -1;
        return;
      }
    } else {
      if (current_entry >= adgMod::block_num_entries) {
        ++current_block;
        current_entry = 0;
        ReadDataBlock();
      }
    }
    ParseEntry();
  }
  
  virtual bool Valid() const { return !block_content.empty(); }

  virtual Slice key() const { 
    assert(Valid());
    return key_;
  }

  virtual Slice value() const { 
    assert(Valid());
    return value_;
  }

  virtual Status status() const { return Status::OK(); }

 private:
	Table* table;
	RandomAccessFile* file;
	adgMod::LearnedIndexData* file_model;
  
  char* scratch = nullptr;
  const uint32_t num_blocks;  
	const uint32_t last_block_num_entries;
  
  Slice block_content;
  uint32_t current_block;
  uint32_t current_entry;

  Slice key_;
  Slice value_;

  void ParseEntry() {
    assert(Valid());
    uint32_t shared, non_shared, value_length;
    const char* key_ptr = DecodeEntry(block_content.data() + current_entry * adgMod::entry_size,
            block_content.data() + adgMod::block_size, &shared, &non_shared, &value_length);
    assert(key_ptr != nullptr && shared == 0 && "Entry Corruption");
    key_ = Slice(key_ptr, non_shared);
    value_ = Slice(key_ptr + non_shared, value_length);
  }

  void ReadDataBlock() {
    uint64_t read_size = current_block == num_blocks - 1 ? last_block_num_entries : adgMod::block_num_entries;
    read_size *= adgMod::entry_size;
    Status s = file->Read(current_block * adgMod::block_size, read_size, &block_content, scratch);
    assert(s.ok());
  }
};






















}