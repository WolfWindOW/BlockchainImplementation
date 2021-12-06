// 
// Transactions.hpp
// Blockguard
//
// Noah Wyborny
// 6/14/2021
//

#include "Transactions.hpp"
/*
CTxIn::CTxIn(std::string prevOutIn) {
	in = prevOutIn;
}


CTxIn::CTxIn(uint32_t hashPrevTx, uint32_t nOut) {
	prevOut = COutPoint(hashPrevTx, nOut);
}


CTxOut::CTxOut(const CAmount& valueIn) {
	value = valueIn;
}
*/
CMutableTransaction::CMutableTransaction() {}
CMutableTransaction::CMutableTransaction(const CTransaction& tx){}

uint32_t CTransaction::computeHash() const {
	return (rand() % MAX_SIZE + 1);
}

CTransaction::CTransaction(const CMutableTransaction& tx) : //vin(tx.vin), vout(tx.vout), 
hash{ computeHash() } {}
CTransaction::CTransaction(CMutableTransaction&& tx) : //vin(std::move(tx.vin)), vout(std::move(tx.vout)), 
hash{ computeHash() } {}