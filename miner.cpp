// 
// miner.cpp
// Blockguard
//
// Noah Wyborny
// 6/15/2021
//

#include <cassert>
#include "miner.hpp"

BlockAssembler::BlockAssembler(std::string id) : Peer(id) {
    genesisBlock();
	pBlockTemplate = createNewBlock();
    tempStorage = std::deque<CTransactionRef>();
	blockQueue = std::deque<CBlock>();
	//checkQueue = std::deque<CBlock>();
    messageQueue = std::deque<message>();
	counter = 0;
	roundCounter = 0;
	//messageFlag = false;
}

BlockAssembler::BlockAssembler(const BlockAssembler& rhs) {
	m_chain = rhs.m_chain;
	counter = rhs.counter;
    tempStorage = rhs.tempStorage;
    messageQueue = rhs.messageQueue;
	blockQueue = rhs.blockQueue;
	//checkQueue = rhs.checkQueue;
	roundCounter = rhs.roundCounter;
	//messageFlag = rhs.messageFlag;
}

void BlockAssembler::resetBlock() {
	//nBlockTx = 0;
}

void BlockAssembler::genesisBlock() {
    resetBlock();
    pBlockTemplate.block.setNull();
    //if (!pBlockTemplate.get())
    //    return;
    CBlock pblock = pBlockTemplate.block;
    pblock.vtx.emplace_back();
    m_chain.setTip(pblock);
}

CBlockTemplate BlockAssembler::createNewBlock() {
	resetBlock();

    pBlockTemplate.block.setNull();

	//if (!pBlockTemplate.get())
	//	return nullptr;

	CBlock pblock = pBlockTemplate.block;

	pblock.vtx.emplace_back();
	/*
	CBlock* pindexPrev = m_chain.Tip();
	assert(pindexPrev != nullptr);
	nHeight = m_chain.Height();
    */
	//pblock->nTime = time(NULL);

	//pblock->hashPrevBlock = pindexPrev->getBlockHash();
	return std::move(pBlockTemplate);
}

void BlockAssembler::addToBlock(const CTransactionRef& tx) {
	pBlockTemplate.block.addTransaction(tx);
}

void BlockAssembler::attemptMine() {
	//If the block has the requisite amount of transactions
    //if (pBlockTemplate.block.getTransactionSize() == DEFAULT_BLOCK_MAX_WEIGHT) {
		//1/n*3 chance of mining
	if (((rand() % (SystemSize * 3)) + 1) == SystemSize) {
		//Makes the block mined, and gets rid of the transactions
		pBlockTemplate.block.setMined(true);
		pBlockTemplate.block.setTransactionAmount(pBlockTemplate.block.getTransactionSize());
		//pBlockTemplate.block.setHash();
		transactionsConfirmed = pBlockTemplate.block.transactions;
		pBlockTemplate.block.clearTxs();
		//Adds the now cleared block to the queue
		CBlock pBlock = pBlockTemplate.block;
		blockQueue.push_back(pBlock);
		//Creates a new block to add transactions to
		pBlockTemplate = createNewBlock();
		//Sets the message flag to true so the new block can be sent out
		//messageFlag = true;
		blocksMade++;
		//Makes the new request such that the message can be sent out immediately
		makeRequest();
	}
	//Ensures that all blocks that were made eventually get into the chain
	//else if (!blockQueue.empty()) makeRequest();
    //}
}

void BlockAssembler::makeRequest() {
    message m;
    //If there is no blocks in queue, send an empty block
	if (blockQueue.size() == 0) {
		m.blocks.setTip(empty);
	}
	//if there are blocks in queue 
	if (blockQueue.size() != 0) {
		//If the block has been mined, send that block
		if (blockQueue.front().mined) {
			//Adds the block to the chain
			m_chain.setTip(blockQueue.front());
			//Adds the block sent to check queue
			//checkQueue.push_back(blockQueue.front());
			//Gets rid of the block in the queue
			blockQueue.pop_front();
			//Adds all the chain to the message
			for (int i = 0; i < m_chain.Size(); i++) {
				m.blocks.setTip(m_chain[i]);
			}
		}
		//If the block somehow got into the queue without being mined, send an empty block
		else { m.blocks.setTip(empty); };
	}
    //Move the message to the queue, and set the flag to false
    messageQueue.push_back(m);
	//messageFlag = false;
}

//TODO Keep block until after the next chain is recieved to make sure it was added, after that is confirmed, then get rid of it, else, rebroadcast

void BlockAssembler::preformComputation() {
	transactionsConfirmed = 0;
	blocksMade = 0;
	for (auto i = 0; i < _inStream.size(); i++) {
		//If there are messages
		//Take the transactions and add them to the transaction pool
		tempStorage.push_back(_inStream[i].getMessage().tx);
		//If the block isnt empty
			if (_inStream[i].getMessage().blocks[0] != empty) {
				/*
				//For each member in check queue
				if (!checkQueue.empty()) {
					//Checks against each block in the message
					for (int l = 0; l < _inStream[i].getMessage().blocks.Size(); l++) {
						//If there is a block that matches the member in check queue
						if (!checkQueue.empty()) {
							if (checkQueue.front() == _inStream[i].getMessage().blocks[l]) {
								//removes it from the queue
								checkQueue.pop_front();
								//If there are more, goes back again next round
								break;
							}
						}
					}
					
				}
				*/
			

				//If the chain we recieved is longer than the one we currently have, swap to the new chain
				if ((m_chain.Size()) < (_inStream[i].getMessage().blocks.Size())) {
					//Clears this peer's chain
					m_chain.clearChain();
					//Adds the new block to the chain
					//Checks against each block in the message
					bool genesisBlock = false;
					for (int k = 0; k < _inStream[i].getMessage().blocks.Size(); k++) {
						/*
						if (!checkQueue.empty()) {
							//If there is a block that matches the member in check queue
							if (checkQueue.front() == _inStream[i].getMessage().blocks[k]) {
								//removes it from the queue
								checkQueue.pop_front();
							}
							*/
							//If the genesis block hasnt been copied, copy it and change flag
							//Or if the block is mined, copy it
							if (!genesisBlock || _inStream[i].getMessage().blocks[k].mined) {
								if (!_inStream[i].getMessage().blocks[k].mined) {
									genesisBlock = true;
								}
								m_chain.setTip(_inStream[i].getMessage().blocks[k]);
							}

							//roundCounter++;
							/*
							//Testing clearing transactions
							for (int j = 0; j < DEFAULT_BLOCK_MAX_WEIGHT; j++) {
								if (!tempStorage.empty()) {
									tempStorage.pop_front();
								}
							}
							*/

						//}
					}
				}
				//Else add the new block
				//Makes sure no single blank block can get through
				else if (_inStream[i].getMessage().blocks.front().mined) {
				/*
					//Checks the front of the queue and the message for matching blocks, if it is matching, removes from queue
					if (_inStream[i].getMessage().blocks.front() == checkQueue.front()) {
						checkQueue.pop_front();
					}
					*/
					m_chain.setTip(_inStream[i].getMessage().blocks.front());

					/*
					for (int j = 0; j < DEFAULT_BLOCK_MAX_WEIGHT; j++) {
						if (!tempStorage.empty()) {
							tempStorage.pop_front();
						}
					}
					*/
				}
			}
		}
/*
	if (!checkQueue.empty()) {
		blockQueue.push_back(checkQueue.front());
		checkQueue.pop_front();
	}
	*/
	//Grabs transactions
	while ((pBlockTemplate.block.getTransactionSize() != DEFAULT_BLOCK_MAX_WEIGHT) && (!(tempStorage.empty()))) {
		if (tempStorage.front() != nullptr) {
			addToBlock(tempStorage.front());
			tempStorage.pop_front();
		}
		else {
			tempStorage.pop_front();
		}
	}

	//One chance to mine, as baseline. One more chance per message sent
	//Mines regardless of whether or not it is full
	if (!(pBlockTemplate.block.mined)) {
		attemptMine();
	}

	while (!(messageQueue.empty())) {
		message mess = messageQueue.front();
		messageQueue.pop_front();
		
		for (auto it = _neighbors.begin(); it != _neighbors.end(); it++) {
			//Create the base message
			message m;
			m.blocks = mess.blocks;
			//Create the transactions
			CMutableTransaction mtx;
			//Create the actual transaction
			CTransaction tx(mtx);
			//Make the transaction reference
			CTransactionRef txRef = MakeTransactionRef(tx);
			//Send the transaction as a message
			m.tx = txRef;
			Packet<message> newM(std::to_string(counter), it->first, _id);
			newM.setBody(m);
			_outStream.push_back(newM);
			counter++;
			//roundCounter++;
		}
		//Only makes transaction per message vs for every neighbor when has a message
		CMutableTransaction mtx;
		CTransaction tx(mtx);
		CTransactionRef txRef = MakeTransactionRef(tx);
		tempStorage.push_back(txRef);
	}

	_inStream.clear();
}


std::ostream& BlockAssembler::printTo(std::ostream& out) const {
    Peer<message>::printTo(out);

    out << _id << std::endl;
    out << "counter:" << counter << std::endl;
    out << "chain length: " << m_chain.Height() << std::endl;

    return out;
}

std::ostream& operator<< (std::ostream& out, const BlockAssembler& peer) {
    peer.printTo(out);
    return out;
}