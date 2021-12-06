// 
// Block.hpp
// Blockguard
//
// Noah Wyborny
// 6/6/2021
//


#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <time.h>
#include <deque>
#include "Transactions.hpp"

static constexpr unsigned int DEFAULT_BLOCK_MAX_WEIGHT = 50;
/*
class CBlockHeader {
public:
	uint32_t nNonce;
	uint32_t hashPrevBlock;
	uint32_t hash = (rand() % MAX_SIZE + 1);
	uint32_t nTime;
	//uint32_t hashMerkleRoot;
	uint32_t nbits;

	static constexpr uint32_t NULL_INDEX = std::numeric_limits<uint32_t>::max();

	CBlockHeader() { setNull(); }

	void setNull() {
		nNonce = 0;
		nbits = 0;
		hash = NULL_INDEX;
		hashPrevBlock = NULL_INDEX;
		nTime = 0;
		//hashMerkleRoot = NULL_INDEX;
	}
	bool isNull() const { return (nbits == 0); }
	uint32_t computeHash() const;

	int64_t getBlockTime() const {
		return(int64_t)nTime;
	}
};
*/
class CBlock //: public CBlockHeader 
{
public:
	std::deque<CTransactionRef> vtx;
	bool mined;
	uint32_t hash;
	time_t timeMined;
	int transactions;

	CBlock() { setNull(); }
	CBlock(const CBlock& rhs) {
		vtx = rhs.vtx;
		mined = rhs.mined;
		hash = rhs.hash;
		timeMined = rhs.timeMined;
		transactions = rhs.transactions;
		//*(static_cast<CBlockHeader*>(this)) = header;
	}
	void setNull() {
		//CBlockHeader::setNull();
		vtx.clear();
		mined = false;
		hash = 0;
		timeMined = 0;
		transactions = 0;
	}

	void setTransactionAmount(const int& amt) {
		transactions = amt;
	}

	void clearTxs() {
		vtx.clear();
	}

	int getTransactionSize() {
		return vtx.size();
	}

	int getTransactionAmount() {
		return transactions;
	}

	void addTransaction(CTransactionRef pTx) {
		if(vtx.size()<DEFAULT_BLOCK_MAX_WEIGHT)	vtx.push_back(pTx);
	}

	void setMined(bool tf) {
		mined = tf;
		if (mined) {
			timeMined = time(NULL);
		}
	}

	void setHash() {
		hash = computeHash();
	}

	time_t getTime() {
		return timeMined;
	}

	uint32_t computeHash() const;

	/*
	CBlockHeader getBlockHeader() const {
		CBlockHeader block;
		block.hashPrevBlock = hashPrevBlock;
		//block.hashMerkleRoot = hashMerkleRoot;
		block.nbits = nbits;
		block.nNonce = nNonce;
		return block;
	}
	*/
	
	friend bool operator==(const CBlock& a, const CBlock& b) { return (a.vtx == b.vtx)&&(a.mined == b.mined)&&(a.timeMined == b.timeMined)&&(a.hash == b.hash); }
	friend bool operator!=(const CBlock& a, const CBlock& b) { return !(a == b); }

};
/*
typedef std::shared_ptr<const CBlock> CBlockRef;
template <typename Cb> static inline CBlockRef MakeCBlockRef(Cb&& CbIn) { return std::make_shared<const CBlock>(std::forward<Cb>(CbIn)); }
*/
#endif
