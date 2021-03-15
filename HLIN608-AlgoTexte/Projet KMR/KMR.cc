#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <map>
#include <stack>
using namespace std;


class KMR {
private:
    const string &ref_seq;
    size_t a, b, e, n;
    std::vector<size_t> v_a;

    void init();
    bool next_iter();

public:
    KMR(const std::string &ref_seq = "");

    const string &getRefSeq() const;
    size_t getRepeatedMotifMaxLength() const;
    size_t getNbRepeatedMotif() const;
    list<size_t> getRepeatedMotifPositions(size_t motif) const;

};

ostream &operator<<(std::ostream &os, const KMR &kmr);

void KMR::init() {
    map<char, size_t> alphabet;
    n = ref_seq.length();
    a = b = 1;
    v_a.resize(n);
    for (size_t i = 0; i < n; ++i) {
        map<char, size_t>::const_iterator it = alphabet.find(ref_seq[i]);
        if (it == alphabet.end()) {
            v_a[i] = alphabet.size();
            alphabet.insert(pair<char, size_t>(ref_seq[i], alphabet.size()));
        } else {
            v_a[i] = it->second;
        }
    }
    e = (alphabet.size() < n ? alphabet.size() : 0);
}

bool KMR::next_iter() {
    vector<stack<size_t> > P(e), Q(e);
    bool has_motif = false;
    cerr << "Nouvelle iteration avec "
         << "a = " << a
         << ", b = " << b
         << " et e ) " << e
         << endl;
    // Empile les positions dans la pile correspondante au motif donné par v_a[i] s'il existe
    for (size_t p = 0; p < n; ++p) {
        if (v_a[p] != (size_t) -1) {
            size_t i = v_a[p];
            P[i].push(p);
        }
    }
    // Dépile les piles P pour remplir les piles Q
    for (size_t i = 0; i < e; ++i) {
        while (!P[i].empty()) {
            size_t p = P[i].top();
            P[i].pop();
            if (((p + b < n) && (v_a[p + b] != (size_t) -1))) {
                Q[v_a[p + b]].push(p);
            }
        }
        for (size_t j = 0; j < e; ++j) {
            if (!Q[j].empty()) {
                size_t x = Q[j].top();
                if (x != (size_t) -1) {
                    Q[j].pop();
                    if (!Q[j].empty()) {
                        size_t y = Q[j].top();
                        if (y != (size_t) -1) {
                            Q[j].push(x);
                            Q[j].push((size_t) -1);
                            has_motif = true;
                        }
                    }
                }
            }
        }
    }

    if (has_motif) {
        fill(v_a.begin(), v_a.end(), (size_t) -1);
        size_t e_tmp = (size_t) -1;
        for (size_t i = 0; i < e; ++i) {
            while (!Q[i].empty()) {
                size_t x = Q[i].top();
                Q[i].pop();
                if (x == (size_t) -1) {
                    ++e_tmp;
                } else {
                    v_a[x] = e_tmp;
                }
            }
        }
        e = ++e_tmp;
        a += b;
        n -= b;
    }

    return has_motif;
}

KMR::KMR(const string &ref_seq): ref_seq(ref_seq) {
    init();
    if (e) {
        do {
            b = a;
        } while (next_iter());
        while (b > 1) {
            b >>= 1;
            next_iter();
        }
    } else {
        a = b = 0;
    }
}

const string &KMR::getRefSeq() const {
    return ref_seq;
}

size_t KMR::getRepeatedMotifMaxLength() const {
    return e ? a : 0;
}

size_t KMR::getNbRepeatedMotif() const {
    return e;
}

list<size_t> KMR::getRepeatedMotifPositions(size_t motif) const {
    list<size_t> positions;
    for (size_t p = 0; p < n; ++p) {
        if (v_a[p] == motif) {
            positions.push_back(p);
        }
    }
    return positions;
}

ostream &operator<<(ostream &os, const KMR &kmr) {
    const string &ref = kmr.getRefSeq();
    if (!kmr.getNbRepeatedMotif()) {
        os << "Il n'y a pas de motif répété dans la séquence '"
           << kmr.getRefSeq()
           << "'.";
    } else {
        os << "La taille maximale du(des) motif(s) répété(s) est " << kmr.getRepeatedMotifMaxLength() << endl
           << "Il y a " << kmr.getNbRepeatedMotif() << " motif(s) répété(s)" << endl;
        for (size_t m = 0; m < kmr.getNbRepeatedMotif(); ++m) {
            list<size_t> pos = kmr.getRepeatedMotifPositions(m);
            os << "Le motif " << (m + 1) << " correspondant à '";
            for (size_t i = 0; i < kmr.getRepeatedMotifMaxLength(); ++i) {
                os << ref[*(pos.begin()) + i];
            }
            os << "' apparaît aux positions : (";
            for (list<size_t>::const_iterator it = pos.begin(); it != pos.end(); ++it) {
                os << (it != pos.begin() ? ", " : "") << (*it + 1);
            }
            os << ")." << endl;
        }
    }
    os << endl;
    return os;
}


int main() {

    KMR test("ABBABBABABBAB");
    operator<<(cout,test) ;
    return 0;
}

