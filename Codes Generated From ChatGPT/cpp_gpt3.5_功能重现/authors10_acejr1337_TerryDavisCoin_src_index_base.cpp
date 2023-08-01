class BaseIndex {
    public:
    virtual bool Init() = 0;
    virtual void ThreadSync() = 0;
    virtual void BlockConnected(const std::shared_ptr<const CBlock>& block, const CBlockIndex* blockIndex) {};
    virtual void ChainStateFlushed(const CBlockLocator&) {};
    virtual void BlockUntilSyncedToCurrentChain(const CBlock&) {};

    static const uint64_t MIN_DISK_SPACE;
    static const unsigned int INDEX_VERSION;

    BaseIndex();
    virtual ~BaseIndex();

    const CBlockIndex* BestBlockIndex() const;
    bool IsSynced() const;
    bool Interrupt() const;
    void Interrupt(bool interrupt);
    void SetSynced(bool synced);
    void WaitUntilSynced() const;

    protected:
    const std::string name_;
    const uint64_t minDiskSpace_;
    const unsigned int indexVersion_;
    CBlockIndex* bestBlockIndex_;
    bool synced_;
    std::atomic<bool> interrupt_;
    std::unique_ptr<std::thread> threadSync_;
};
#include <bitcoin/index/base_index.h>
#include <bitcoin/index/indexdb.h>

class BaseIndex: public Index {
    public:
    BaseIndex(const std::string& name, const Config& config, IndexDB& indexdb)
        : Index(name, config, indexdb), best_block_index_(nullptr), synced_(false), interrupt_(false),
        thread_sync_(nullptr) {}

    bool Init() override {
        // Read index data from the IndexDB database
        // Set BestBlock to the last synced block
        best_block_index_ = LoadBestBlockIndex();
        return best_block_index_ != nullptr;
    }

    void ThreadSync() override {
        // Create a dedicated thread to sync unsynced blocks
        // Mark index as synced when done
        if (!synced_ && !interrupt_ && thread_sync_ == nullptr) {
            thread_sync_ = new std::thread(&BaseIndex::SyncThread, this);
        }
    }

    virtual void BlockConnected(const std::shared_ptr<const CBlock>& block,
        const CBlockIndex* block_index) {}
    virtual void ChainStateFlushed(const CBlockLocator& locator) {}
    virtual void BlockUntilSyncedToCurrentChain() {}

    protected:
        // Load the best block index from the IndexDB database
    virtual const CBlockIndex* LoadBestBlockIndex() const {
        return indexdb_.GetBestIndex();
    }

    // A dedicated thread to sync unsynced blocks
    void SyncThread() {
        // TODO: Implement block sync logic
        synced_ = true;
        thread_sync_ = nullptr;
    }

    const CBlockIndex* best_block_index_;
    bool synced_;
    bool interrupt_;
    std::thread* thread_sync_;
};
