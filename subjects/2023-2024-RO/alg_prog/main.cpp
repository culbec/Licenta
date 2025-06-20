#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>

#define DEFAULT_CIRCULAR_ENCODING_LENGTH 2

class Encoder
{
public:
    virtual std::string encode(const std::string &m) const = 0;

    virtual ~Encoder() = default;
};

class NaiveEncoding : public Encoder
{
public:
    NaiveEncoding() : Encoder{} {}

    std::string encode(const std::string &m) const
    {
        std::string result{m};
        auto resultSize = result.size();
        size_t i = 0, j = resultSize - 1;

        while (i < j)
        {
            auto temp = result[i];
            result[i] = result[j];
            result[j] = temp;

            i++;
            j--;
        }

        return result;
    }

    ~NaiveEncoding() = default;
};

class CircularEncoding : public Encoder
{
private:
    int length;

public:
    CircularEncoding() : Encoder{}, length{DEFAULT_CIRCULAR_ENCODING_LENGTH} {}

    CircularEncoding(int length) : Encoder{}
    {
        this->length = length < 2 ? DEFAULT_CIRCULAR_ENCODING_LENGTH : length;
    }

    std::string encode(const std::string &m) const
    {
        std::string result{m};
        auto mSize = m.size();

        for (size_t i = 0; i < mSize; i++)
        {
            result[i] = m[(i + this->length) % mSize];
        }

        return result;
    }

    ~CircularEncoding() = default;
};

class Communication
{
private:
    Encoder *code;
    std::vector<std::string> encodedMessages;

public:
    Communication() : code{new NaiveEncoding{}} {}
    Communication(Encoder *e)
    {
        this->code = e == nullptr ? new NaiveEncoding{} : e;
    }

    // Communication(const Communication& other) {
    //     if (this == &other) {
    //         return;
    //     }

    //     if (this->code != nullptr) {
    //         delete this->code;
    //     }

    // !     // create deep copy of other.code
    // !     // not possible here because we do not know the type of the child class that inherits of Encoder
    // }

    // Communication& operator=(const Communication& other) {
    //     if (this == &other) {
    //         return *this;
    //     }

    //     if (this->code != nullptr) {
    //         delete this->code;
    //     }

    // !     // create deep copy of other.code
    // !     // not possible here because we do not know the type of the child class that inherits of Encoder
    // }

    void addMessage(const std::string &m)
    {
        auto encoded = this->code->encode(m);
        this->encodedMessages.push_back(encoded);
    }

    const std::vector<std::string> &getEncodedMessages() const { return this->encodedMessages; }

    std::string toString() const
    {
        std::string result{};

        for (size_t i = 0; i < this->encodedMessages.size(); i++)
        {
            result += this->encodedMessages[i];

            if (i != this->encodedMessages.size() - 1)
            {
                result += '#';
            }
        }

        return result;
    }

    ~Communication()
    {
        if (this->code != nullptr)
        {
            delete this->code;
            this->code = nullptr;
        }
    }
};

std::vector<std::string> mergeAlphabeticSortedStringListsHelper(const std::vector<std::string> &L1, size_t indexL1, const std::vector<std::string> &L2, size_t indexL2)
{
    if (indexL1 >= L1.size() && indexL2 >= L2.size())
    {
        return std::vector<std::string>{};
    }
    else if (indexL1 < L1.size() && indexL2 >= L2.size())
    {
        auto result = mergeAlphabeticSortedStringListsHelper(L1, indexL1 + 1, L2, indexL2);
        result.push_back(L1.at(indexL1));
        return result;
    }
    else if (indexL1 >= L1.size() && indexL2 < L2.size())
    {
        auto result = mergeAlphabeticSortedStringListsHelper(L1, indexL1, L2, indexL2 + 1);
        result.push_back(L2.at(indexL2));
        return result;
    }

    // merging from the beginning of the lists to the end, recursively
    if (L1.at(indexL1) < L2.at(indexL2))
    {
        // addding L1[i]
        auto result = mergeAlphabeticSortedStringListsHelper(L1, indexL1 + 1, L2, indexL2);
        result.push_back(L1.at(indexL1));
        return result;
    }

    // adding L2[i]
    auto result = mergeAlphabeticSortedStringListsHelper(L1, indexL1, L2, indexL2 + 1);
    result.push_back(L2.at(indexL2));
    return result;
}

//* b)
/**
 * Merges the alphabetically sorted lists of strings L1 and L2, recursively
 *
 * @param L1: the first list of strings
 * @param L2: the second list of strings
 * @return std::vector<std::string>: L1 and L2 merged
 */
std::vector<std::string> mergeAlphabeticSortedStringLists(const std::vector<std::string> &L1, const std::vector<std::string> &L2)
{
    return mergeAlphabeticSortedStringListsHelper(L1, 0, L2, 0);
}

//* c)
bool checkCircularEncoding(const std::string &m1, const std::string &m2)
{
    if (m1.size() != m2.size())
    {
        return false;
    }

    // if the messages are equal, that means a circular encoding with 'm.size()' or '0' positions
    if (m1 == m2)
    {
        return true;
    }

    // for each starting index in [0, m.size()), we need to check if we can go from m1 to m2
    // in a circular encoding manner
    auto mSize = m1.size();
    for (size_t startPoint = 1; startPoint < mSize; startPoint++)
    {
        bool found = true;
        for (size_t i = 0; i < mSize && found; i++)
        {
            // checking if the character at position 'i' in m1 is startPoint position to the right in m2
            if (m1.at(i) != m2.at((i + startPoint) % mSize))
            {
                found = false;
            }
        }

        if (found)
        {
            return true;
        }
    }

    return false;
}

//* d)
size_t numberOfDistinctMessages(const Communication &c)
{
    if (c.getEncodedMessages().size() == 0)
    {
        return 0;
    }

    std::unordered_map<std::string, size_t> messageAppearancesMapping{};

    for (const auto &m : c.getEncodedMessages())
    {
        auto iter = messageAppearancesMapping.find(m);

        if (iter != messageAppearancesMapping.end())
        {
            messageAppearancesMapping[m] += 1;
        }
        else
        {
            messageAppearancesMapping[m] = 1;
        }
    }

    size_t result = 0;

    for (const auto &m : messageAppearancesMapping)
    {
        result += m.second == 1 ? 1 : 0;
    }

    return result;
}

//* e)
int main()
{
    Communication o1{new CircularEncoding{10}};
    Communication o2{new NaiveEncoding{}};

    o1.addMessage("bac"); o1.addMessage("cod"); o1.addMessage("apt");
    o2.addMessage("bac"); o2.addMessage("cod"); o2.addMessage("apt");

    auto mergedList = mergeAlphabeticSortedStringLists(o1.getEncodedMessages(), o2.getEncodedMessages());
    for (const auto& elem: mergedList) {
        std::cout << elem << " ";
    }
}

//* f) functia mergeAlphabeticSortedStringLists are complexitatea Theta(m + n), fiind necesar sa se parcurga ambele liste pentru a
//*     sorta interclasa continutul ambelor liste
//*     BEST = WORST = AVERAGE = Theta(m + n)

//* g) COMPLEXITATE ADAUGARE IN TABELA DE DISPERSIE UNDE CHEIA ESTE CHEIE NATURALA
//*     BEST:       cheia K nu se afla in tabela de dispersie sau se afla deja  =====> Theta(1)
//*     WORST:      depinde cum se rezolva coliziunile                          =====> O(n)
//*                 -   OPEN ADDRESSING: 
//*                     - LINEAR PROBING:       O(n)        - nu exista pozitii libere + Theta(n) in caz de resize => O(n)
//*                     - QUADRATIC PROBING:    O(n)        - nu exista pozitii libere + Theta(n) in caz de resize => O(n)
//*                     - DOUBLE HASHING:       O(n)        - pentru resize in caz ca nu exista pozitii libere
//*                 -   SEPARATE CHAINING: Theta(bucket_size) pt cautare pozitie in bucket + Theta(n) pt resize ==> O(n)
//*     AVERAGE:    O(1) in caz amortizat, deoarece sunt rare cazurile in care nu vom avea spatiu disponibil pentru noua cheie K
//*                 daca avem o functie buna de rehash si load balancing mic
//*     TOTAL COMPLEXITY: O(1)
