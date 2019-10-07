#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
  public:
    // Use two sets to store frontier words (bidirectional)
    // Instead of looping, use 26 letter and perform search
    // Choose the shorter list for searching
    // Swap is really handy
    int ladderLengthSample(string beginWord, string endWord, vector<string>& wordList) {
      unordered_set<std::string> dictionary(wordList.begin(), wordList.end());
      unordered_set<std::string> head, tail, *pHead, *pTail;

      if(dictionary.count(endWord) == 0) {
        return 0;
      }

      head.insert(beginWord);
      tail.insert(endWord);
      int ladderLength = 2;
      while(!head.empty() && !tail.empty()) {

        if(head.size() < tail.size()) {
          pHead = &head;
          pTail = &tail;
        } else {
          pHead = &tail;
          pTail = &head;
        }

        std::unordered_set<std::string> tempSet;
        for(auto itr = pHead->begin(); itr != pHead->end(); ++itr) {
          std::string str = *itr;
          for(int i = 0; i < str.size(); ++i) {
            char temp = str[i];

            for(int j = 0; j < 26; ++j) {
              str[i] = 'a' + j;

              if(pTail->count(str)) {
                return ladderLength;
              }

              if(dictionary.count(str)) {
                tempSet.insert(str);
                dictionary.erase(str);
              }
            }


            str[i] = temp;
          }
        }

        ++ladderLength;
        pHead->swap(tempSet);

      }


      return 0;
    }

    // There's no reference for string
    // 89.70%
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
      int S = beginWord.size();
      unordered_map<string, int> dict;
      for(string& s: wordList) dict.insert({s, 0});

      // Edge case, endWord doesn't exsist
      if(dict.find(endWord) == dict.end()) return 0;
      else dict[endWord] = -1;

      // Edge case, beginWord also in list
      if(dict.find(beginWord) == dict.end()) dict.insert({beginWord, 1});
      else dict[beginWord] = 1;

      queue<string> searchList;
      searchList.push(beginWord);
      searchList.push(endWord);

      bool reverse;
      int currStep, compareStep;
      char c;
      while(!searchList.empty()) {
        string currStr = searchList.front();
        searchList.pop();

        currStep = dict[currStr];
        reverse = currStep < 0;

        for(int i = 0; i < S; i++) {
          c = currStr[i];
          // Mark all words differ by one
          for(int j = 0; j < 26; j++) {
            if(c-'a' == j) continue;

            currStr[i] = 'a'+j;

            if(dict.find(currStr) != dict.end()) {
              compareStep = dict[currStr];
              if(reverse && compareStep > 0) {
                return compareStep-currStep;
              } else if(!reverse && compareStep < 0) {
                return currStep-compareStep;
              } else if(compareStep == 0) {
                dict[currStr] = currStep+(reverse? -1:1);
                searchList.push(currStr);
              }
            }
          }

          // Restore string
          currStr[i] = c;
        }
      }

      return 0;
    }

    // A good question: how large is the input?
    // 46.37% not good; 100% space though
    // It's a dictionary file! A huge number of words in word list!
    int ladderLengthLoop(string beginWord, string endWord, vector<string>& wordList) {
      int N = wordList.size();
      int S = beginWord.size();
      int endIdx = -1;

      // Test endWord in the list
      for(int i = 0; i < N; i++) {
        if(wordList[i].compare(endWord) == 0) {
          endIdx = i;
          break;
        }
      }
      // endWord not in list
      if(endIdx == -1) return 0;
      // cout << endIdx << endl;

      vector<int> steps(N, 0);
      queue<int> tempList;
      tempList.push(-1);
      tempList.push(endIdx);
      steps[endIdx] = -1;

      bool differByOne, reverse;
      int currIdx, currStep;
      while(!tempList.empty()) {
        currIdx = tempList.front();
        tempList.pop();
        string& currStr = (currIdx == -1? beginWord: wordList[currIdx]);
        currStep = (currIdx == -1? 1: steps[currIdx]);
        reverse = currStep < 0;

        // Explore words in the list
        for(int i = 0; i < N; i++) {
          // Only test words that are unexplored or in reverse direction
          if((reverse && steps[i] >= 0) || (!reverse && steps[i] <= 0)) {
            string& compareStr = wordList[i];
            differByOne = false;

            for(int j = 0 ; j < S; j++) {
              if((currStr[j] ^ compareStr[j]) != 0) {
                if(!differByOne) differByOne = true;
                else {
                  differByOne = false;
                  break;
                };
              }
            }


            // Test successful search
            if(differByOne) {
              // Two directions meet
              if(currStep < 0 && steps[i] > 0) {
                return steps[i]-currStep;
              } else if(currStep > 0 && steps[i] < 0) {
                return currStep-steps[i];
              }

              // Found a path
              if(reverse) steps[i] = currStep-1;
              else steps[i] = currStep+1;
              tempList.push(i);
            }
          }
        }
      }

      // Can't find a path
      return 0;
    }
};

int main() {
  Solution s;
  vector<string> list = {"kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes","ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit","rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut","sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu","ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan","map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi","sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib","mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum","pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag","hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam",
    "ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy",
    "due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad",
    "hah","hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big","ilk","gal","tap","duh","ola","ran","lab","top","gob","hot","ora","tia","kip","han","met","hut","she","sac","fed","goo","tee","ell","not","act","gil","rut","ala","ape","rig","cid","god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her","nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid","mai","sup","jay","hob","mow","jot","are","pol","arc","lax","aft","alb","len","air","pug","pox","vow","got","meg","zoe","amp","ale","bud","gee","pin","dun","pat","ten","mob"};
  string beginWord = "cet";
  string endWord = "ism";

  cout << "Path num: " << s.ladderLength(beginWord, endWord, list) << endl;
}
