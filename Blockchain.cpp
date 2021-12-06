// 
// Blockchain.cpp
// Blockguard
//
// Noah Wyborny
// 6/14/2021
//

#include <assert.h>
#include "Blockchain.hpp"

void CChain::setTip(CBlock pindex) {
	/*
	if (pindex == block) {
		vChain.clear();
		//timeAdded = time(NULL);
		return;
	}
	*/
	//vChain.resize(vChain.size()+1);
	//while (vChain[vChain.size()] != pindex) {
		vChain.push_back(pindex);
		//pindex = pindex->pprev;
		//timeAdded = time(NULL);
	//}

}
/*
const CBlockIndex* CChain::findFork(const CBlock* pindex) const {
	if (pindex == nullptr) {
		return nullptr;
	}
	if (pindex->nHeight > Height()) pindex = pindex->getAncestor(Height());
	while (pindex && !Contains(pindex)) {
		pindex = pindex->pprev;
	}
	return pindex;
}

//Turn the lowest '1' bit into a '0'
int static inline invertLowestOne(int n) { return n & (n - 1); }

//Compute what height to jump back to
int static inline getSkipHeight(int height) {
	if (height < 2) return 0;
	return (height & 1) ? invertLowestOne(invertLowestOne(height - 1)) + 1 : invertLowestOne(height);
}
*/
/*
const CBlockIndex* CBlockIndex::getAncestor(int height) const {
	if (height > nHeight || height < 0) return nullptr;
	const CBlockIndex* pindexWalk = this;
	int heightWalk = nHeight;
	while (heightWalk > height) {
		int heightSkip = getSkipHeight(heightWalk);
		int heightSkipPrev = getSkipHeight(heightWalk - 1);
		if (pindexWalk->pskip != nullptr &&
			(heightSkip == height ||
				(heightSkip > height && !(heightSkipPrev < heightSkip - 2 && heightSkipPrev >= height)))) {
			pindexWalk = pindexWalk->pskip;
			heightWalk = heightSkip;
		}
		else {
			assert(pindexWalk->pprev);
			pindexWalk = pindexWalk->pprev;
			heightWalk--;
		}
	}
	return pindexWalk;
}

CBlockIndex* CBlockIndex::getAncestor(int height) {
	return const_cast<CBlockIndex*>(static_cast<const CBlockIndex*>(this)->getAncestor(height));
}

const CBlockIndex* LastCommonAncestor(const CBlockIndex* pa, const CBlockIndex* pb) {
	if (pa->nHeight > pb->nHeight) {
		pa = pa->getAncestor(pb->nHeight);
	}
	else if (pb->nHeight > pa->nHeight) {
		pb = pb->getAncestor(pa->nHeight);
	}

	while (pa != pb && pa && pb) {
		pa = pa->pprev;
		pb = pb->pprev;
	}

	assert(pa == pb);
	return pa;
}
*/