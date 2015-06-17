BvSet_t partition(BV &input)const {
  BV b;
  return MinCutConservative(input, b, b);
};

BvSet_t MinCutConservative(BV &subRels, BV &connectedRels, BV &excluded) const {
  BvSet_t result;
  if (connectedRels == subRels) return result;
  if (connectedRels.is_not_empty())  result.insert({connectedRels, getNeighbors(connectedRels, subRels)});
  BV excl_new = excluded;
  BV neighb = getNeighbors(connectedRels, subRels);
  neighb.intersect_with(subRels);
  neighb = neighb.without(excluded);
  for (unsigned int i = 0; i < neighb.capacity(); ++i) {
    if (neighb.test(i)) {
	  BV v; v.set(i);
	  BvSet_t O = getConnectedParts(subRels, connectedRels.uni(v), v);
	  excl_new.union_with(v);
	  for (BV o : O) {
		BV newConRels;
		newConRels = subRels.without(o);
		BvSet_t r = MinCutConservative(subRels, newConRels, excl_new);
		result.insert(r.begin(), r.end());
	  }
    }
  }
  return result;
}