// 
// Blockchain.hpp
// Blockguard
//
// Noah Wyborny
// 6/14/2021
//

#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include "Block.hpp"
/*
class CBlockFileInfo {
public:
	unsigned int nBlocks; //Number of blocks stored
	unsigned int nSize; //Number of used bytes of block file
	unsigned int nHeightFirst; //Lowest height of block in file
	unsigned int nHeightLast; //Highest height of block in file
	uint64_t nTimeFirst; //Earliest time of block
	uint64_t nTimeLast; //Latest time of block

	void setNull() {
		nBlocks = 0;
		nSize = 0;
		nHeightFirst = 0;
		nHeightLast = 0;
		nTimeFirst = 0;
		nTimeLast = 0;
	}

	CBlockFileInfo() {
		setNull();
	}

	void AddBlock(unsigned int nHeightIn, uint64_t nTimeIn) {
		if (nBlocks == 0 || nHeightFirst > nHeightIn) nHeightFirst = nHeightIn;
		if (nBlocks == 0 || nTimeFirst > nTimeIn) nTimeFirst = nTimeIn;
		nBlocks++;
		if (nHeightIn > nHeightLast) nHeightLast = nHeightIn;
		if (nTimeIn > nTimeLast) nTimeLast = nTimeIn;
	}
};

class CBlockIndex {
public:
	//Pointer to hash of the block
	const uint32_t* phashblock{ nullptr };
	//Pointer to the index of the predecessor of the block
	CBlockIndex* pprev{ nullptr };
	//Pointer to the index of some further predecessor of this block
	CBlockIndex* pskip{ nullptr };
	//Height of the entry in the chain. Genesis block height == 0
	int nHeight{ 0 };
	//Number of transactions in this block
	unsigned int nTx{ 0 };
	//Number of transactions in the chain up to and including this block
	unsigned int nChainTx{ 0 };

	//uint32_t hashMerkleRoot{};
	//uint32_t nbits{ 0 };
	uint32_t nNonce{ 0 };

	CBlockIndex() {}

	explicit CBlockIndex(const CBlockHeader& block)
		: //hashMerkleRoot{ block.hashMerkleRoot },
		//nbits{ block.nbits },
		nNonce{ block.nNonce }
	{
	}

	CBlockHeader getBlockHeader() const {
		CBlockHeader block;
		if (pprev) block.hashPrevBlock = pprev->getBlockHash();
		//block.hashMerkleRoot = hashMerkleRoot;
		//block.nbits = nbits;
		block.nNonce = nNonce;
		return block;
	}

	unsigned int getTransactionNumber() const {
		return nTx;
	}

	uint32_t getBlockHash() const {
		return *phashblock;
	}

	bool haveTxsDownloaded() const { return nChainTx != 0; }

	CBlockIndex* getAncestor(int height);
	const CBlockIndex* getAncestor(int height) const;
};
*/

class CChain {
private:
	std::vector<CBlock> vChain;
public:
	//time_t timeAdded;
	//Returns the index entry for the genesis block, or nullptr if does not exist
	/*
	CBlock Genesis() const {
		return vChain.size() > 0 ? vChain[0] : nullptr;
	}
	//Returns the index entry for the tip of the chain, or nullptr if does not exist
	CBlock Tip() const {
		return vChain.size() > 0 ? vChain[vChain.size() - 1] : nullptr;
	}
	//Returns index entry at a height in the chain or nullptr if does not exist
	*/
	CBlock operator[](int height) const {
		if (height < 0 || height >= (int)vChain.size()) {
			CBlock block;
			return block;
		}
		return vChain[height];
	}
	//Is block in chain
	/*
	bool Contains(const CBlock pindex) const {
		for (auto i = 0; i < vChain.size(); i++) {
			if (pindex == vChain[i]) return true;
		}
		return false;
	}
	*/
	CBlock removeTip() {
		vChain.pop_back();
	}
	void clearChain() {
		vChain.clear();
	}
	//Find successor of block, or nullptr if not found or is the tip
	/*
	CBlockIndex* Next(const CBlock* pindex) const {
		if (Contains(pindex)) return (*this)[pindex->nHeight + 1];
		else return nullptr;
	}
	*/
	//Return max height

	CBlock front() const {
		return vChain.front();
	}

	int Height() const {
		return vChain.size() - 1;
	}
	int Size() const {
		return vChain.size();
	}
	int getTransactionAmt() const {
		int result = 0;
		for (int i = 0; i < vChain.size(); i++) {
			result += vChain[i].transactions;
		}
		return result;
	}
	//Initialize a chain with a given tip
	void setTip(CBlock pindex);
	//Find last common block between chain and block index
	/*
	const CBlockIndex* findFork(const CBlockIndex* pindex) const;
	*/
	/*
	time_t getTime() {
		return timeAdded;
	}
	*/
};

#endif // !BLOCKCHAIN_HPP
