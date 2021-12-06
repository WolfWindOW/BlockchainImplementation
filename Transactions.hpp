// 
// Transactions.hpp
// Blockguard
//
// Noah Wyborny
// 6/6/2021
//



#ifndef TRANSACTIONS_HPP
#define TRANSACTIONS_HPP

#include <vector>
#include <string>
#include <memory>
#include "Wallet.hpp"


struct CMutableTransaction;
/*
class COutPoint {
public:
	uint32_t hash;
	uint32_t n;

	static constexpr uint32_t NULL_INDEX = std::numeric_limits<uint32_t>::max();

	COutPoint() { SetNull(); }
	COutPoint(const uint32_t hashIn, uint32_t nIn) : hash(hashIn), n(nIn) {}

	void SetNull() { hash = NULL_INDEX; n = NULL_INDEX; };
	bool IsNull() const { return (hash == NULL_INDEX && n == NULL_INDEX); };

	friend bool operator==(const COutPoint& a, const COutPoint& b) { return (a.hash == b.hash && a.n == b.n); }
	friend bool operator!=(const COutPoint& a, const COutPoint& b) { return !(a == b); }
};
*/
/*
class CTxIn {
public:
	//COutPoint prevOut;
	std::string in;

	explicit CTxIn(std::string in);
	//CTxIn(uint32_t hashPrevTx, uint32_t nOut);

	friend bool operator==(const CTxIn& a, const CTxIn& b) { return a.in == b.in; }
	friend bool operator!=(const CTxIn& a, const CTxIn& b) { return !(a == b); }
};

class CTxOut {
public:
	CAmount value;
	std::string out;
	CTxOut() { SetNull(); };
	CTxOut(std::string outV) {
		SetNull();
		out = outV;
	};
	CTxOut(const CAmount& valueIn);
	void SetNull() { value = 0; };

	friend bool operator==(const CTxOut& a, const CTxOut& b) { return a.value == b.value; }
	friend bool operator!=(const CTxOut& a, const CTxOut& b) { return !(a == b); }
};
*/
class CTransaction {
public:
	//const std::vector<CTxIn> vin;
	//const std::vector<CTxOut> vout;
	const uint32_t hash = (rand() % MAX_SIZE + 1);

private:
	uint32_t computeHash() const;
public:
	explicit CTransaction(const CMutableTransaction& tx);
	CTransaction(CMutableTransaction&& tx);

	//bool IsNull() const { return vin.empty() && vout.empty(); }
	const uint32_t getHash() const { return hash; }
	//bool IsCoinBase() const { return (vin.size() == 1 && vin[0].prevOut.IsNull()); }

	friend bool operator==(const CTransaction& a, const CTransaction& b) { return a.hash == b.hash; }
	friend bool operator!=(const CTransaction& a, const CTransaction& b) { return !(a == b); }
};

struct CMutableTransaction {
	//std::vector<CTxIn> vin;
	//std::vector<CTxOut> vout;

	CMutableTransaction();
	explicit CMutableTransaction(const CTransaction& tx);
};

typedef std::shared_ptr<const CTransaction> CTransactionRef;
template <typename Tx> static inline CTransactionRef MakeTransactionRef(Tx&& txIn) { return std::make_shared<const CTransaction>(std::forward<Tx>(txIn)); }

#endif
