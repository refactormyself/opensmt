//
//
//

#include "LARefs.h"
#include "Polynomials.h"
#include "BindedRows.h"
Poly::Poly(Poly &old, int new_cap) : id(old.id), cap(new_cap), sz(old.sz), var(old.var)
{
    for (int i = 0; i < old.size(); i++)
        terms[i] = old.terms[i];
}

Poly::Poly(vec<PolyTermRef>& ps, LVRef var, int id) : id(id), var(var) {
    cap = sz = ps.size();
    for (int i = 0; i < ps.size(); i++)
        terms[i] = ps[i];
}

//
// Update the polynomial, positions, and binded rows.
//
void
PolyStore::remove(LVRef v, PolyRef pol)
{
    Poly& p = pa[pol];
    brs.remove(pol, v);

    Map<LVRef,int,LVRefHash>& positions = varToIdx[pa[pol].getId()];
    int start_idx = positions[v]+1;
    positions.remove(v);
    for (int i = start_idx; i < p.size(); i++) {
        LVRef w = pta[p[i]].var;
        positions[w] = i-1;
        p[i - 1] = p[i];
        brs.remove(pol, w);
        brs.add(pol, i-1, w);
    }
    p.sz --;
    assert(positions.getSize()== p.sz);
    checkConsistency(pol);
}

void PolyStore::remove(LVRef poly_var)
{
    remove(lva[poly_var].getPolyRef());
}

void
PolyStore::remove(PolyRef pr)
{
    for (int i = 0; i < pa[pr].size(); i++) {
        brs.remove(pr, pta[pa[pr][i]].var);
    }
    for (int i = 0; i < pa[pr].size(); i++) {
        // Remove the PolyTermRef
        PolyTermRef ptr = pa[pr][i];
        pta.free(ptr);
    }
    pa.free(pr);
}

int
PolyStore::add(PolyRef pr, LVRef v, Real &c) {
    assert(!lva[v].isBasic());
    int pos;
    Poly& poly = pa[pr];
    LVRef poly_var = poly.getVar();
    Map<LVRef,int,LVRefHash>& positions = varToIdx[poly.getId()];
    if (positions.has(v)) {
        pos = positions[v];
        PolyTermRef v_term = poly[positions[v]];
        pta.updateCoef(v_term, pta[v_term].coef + c);
        if (pta[v_term].coef == 0) {
            pta.free(v_term);
            remove(v, pr);
            pos = -1;
        }
    }
    else {
        PolyRef pr_new = pr;
        if (pa[pr].getUnusedCap() == 0) {
            // We need to allocate a new polynomial with bigger capacity.
            pr_new = pa.alloc(pr, poly.size() > 0 ? poly.size() * 2 : 1);
            lva[poly_var].setPolyRef(pr_new);
            Poly& p = pa[pr_new];
            for (int i = 0; i < p.size(); i++) {
                const PolyTerm &pt = pta[p[i]];
                BindedRows &br = brs.getBindedRows(pt.var);
                for (int j = 0; j < br.size(); j++) {
                    if (br[j].poly == pr) {
                        br.updatePolyRef(j, pr_new);
                        break;
                    }
                }
            }
        }
        Poly& poly_upd = pa[pr_new];
        poly_upd.append(pta.alloc(c, v), v);
        pos = poly_upd.size()-1;
        positions.insert(v, pos);
        brs.add(pr_new, pos, v);
        assert(checkConsistency(pr_new));
    }
    return pos;
}



void PolyStore::updateTerm(PolyRef pr, PolyTermRef term, LVRef var, const opensmt::Real& coef) {
    LVRef old_var = pta[term].var;
    pta.updateVar(term, var);
    pta.updateCoef(term, coef);
    Map<LVRef, int, LVRefHash> &positions = varToIdx[pa[pr].getId()];
    int idx = positions[old_var];
    positions.remove(old_var);
    positions.insert(var, idx);
    brs.remove(pr, old_var);
    brs.add(pr, idx, var);
    checkConsistency(pr);
}

char* PolyStore::printPolyTerm(const opensmt::Real &coef, LVRef var)
{
    if (coef == 1)
        return lva.printVar(var);

    char *buf;
    if (coef == -1)
        asprintf(&buf, "-%s", lva.printVar(var));
    else {
        const char *coef_str = coef.get_str().c_str();
        asprintf(&buf, "(* %s %s)", coef_str, lva.printVar(var));
    }
    return buf;
}

char* PolyStore::printPoly(PolyRef pr)
{
    Poly &p = pa[pr];
    char *buf = NULL;
    for (int i = 0; i < p.size(); i++) {
        char *buf_new;
        const PolyTerm& pt = pta[p[i]];
        asprintf(&buf_new, "%s %s", (buf == NULL ? "" : buf), printPolyTerm(pt.coef, pt.var));
        free(buf);
        buf = buf_new;
    }
    char *buf_new;
    asprintf(&buf_new, "%s = (+%s)", lva.printVar(p.var), buf == NULL ? "" : buf);
    free(buf);
    return buf_new;
}

char* PolyStore::printOccurrences(LVRef var)
{
    char* buf = NULL;
    char *buf_new;
    BindedRows& b = brs.getBindedRows(var);
    for (int i = 0; i < b.size(); i++) {
        asprintf(&buf_new, "%s (%s, pos %d)", (buf == NULL ? "" : buf), printPoly(b[i].poly), b[i].pos);
        free(buf);
        buf = buf_new;
    }
    asprintf(&buf_new, "(%s)", buf == NULL ? "" : buf);
    free(buf);
    return buf_new;
}

PolyRef
PolyStore::makePoly(LVRef s, vec<PolyTermRef>& terms)
{
    PolyRef pr = pa.alloc(terms, s);
    lva[s].setPolyRef(pr);
    assert(pa[pr].getId() == varToIdx.size());
    varToIdx.push();
    Map<LVRef,int,LVRefHash>& positions = varToIdx.last();
    for (int i = 0; i < terms.size(); i++) {
        positions.insert(pta[terms[i]].var, i);
        brs.add(pr, i, pta[terms[i]].var);
    }
    checkConsistency(pr);
    return pr;
}

bool PolyStore::checkConsistency(PolyRef pr)
{
    Poly& p = pa[pr];
    Map<LVRef,int,LVRefHash>& positions = varToIdx[pa[pr].getId()];
    for (int i = 0; i < p.size(); i++) {
        LVRef prs_var = pta[p[i]].var;
        if (positions[prs_var] != i) {
            assert(false);
            return false;
        }
        BindedRows& rows_binded_to_prs_var = brs.getBindedRows(prs_var);
        for (int j = 0; j < rows_binded_to_prs_var.size(); j++) {
            BindedRow r = rows_binded_to_prs_var[j];
            if (r.poly== pr) {
                if (r.pos != i) {
                    assert(false);
                    return false;
                }
            }
        }
    }
    return true;
}