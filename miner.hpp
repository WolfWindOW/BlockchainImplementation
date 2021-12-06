// 
// Blockchain.hpp
// Blockguard
//
// Noah Wyborny
// 6/15/2021
//

#ifndef MINER_HPP
#define MINER_HPP

#include "Blockchain.hpp"
#include "MemoryPool.hpp"
#include "\Users\ynrob\Downloads\distributed-consensus-abstract-simulator-master\distributed-consensus-abstract-simulator-master\BlockGuard\Common\Peer.hpp"

struct CBlockTemplate {
	CBlock block;
};

struct message {
	CTransactionRef tx;
	CChain blocks;
	//int height;
};

class BlockAssembler : public Peer<message> 
{
protected:
	int roundCounter;
	int counter;
private:
	CBlockTemplate pBlockTemplate;
	CBlock empty; //An empty block to be sent if this node hasnt finished its block
	CChain m_chain;
	//MemoryPool* txpool;
	std::deque<message> messageQueue;
	std::deque<CTransactionRef> tempStorage;
	std::deque<CBlock> blockQueue;
	//std::deque<CBlock> checkQueue;
	int blocksMade;
	int transactionsConfirmed;
	//Config param
	//unsigned int nBlockMaxWeight = DEFAULT_BLOCK_MAX_WEIGHT;
	//Info on block
	//uint64_t nBlockTx;
	//Chain context for block
	//int nHeight;
	//CChain& m_chain;
public:
	explicit BlockAssembler(std::string);
	BlockAssembler(const BlockAssembler& rhs);
	~BlockAssembler() {};
	void attemptMine();
	void makeRequest();
	void preformComputation();
	void log() const { printTo(*_log); };
	std::ostream& printTo(std::ostream&) const;
	CBlockTemplate createNewBlock();
	void genesisBlock();


	friend std::ostream& operator<< (std::ostream&, const BlockAssembler&);

	int getCounter()const { return counter; };
	void setCounter(int c) { counter = c; };
	int getChainLength() const { return m_chain.Height(); };
	int getBlocksCreated() const {return blocksMade;};
	int getRoundCounter() const { return roundCounter; };
	int getTransactionsConfirmed() const { return transactionsConfirmed; };
	//bool getMessageFlag() const { return messageFlag; };
	int getTransactionAmount() const { return m_chain.getTransactionAmt(); };
private:
	void resetBlock();
	void addToBlock(const CTransactionRef&);
};

#endif // !MINER_HPP
