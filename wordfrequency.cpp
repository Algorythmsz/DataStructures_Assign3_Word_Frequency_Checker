#include "wordfrequency.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

WordFrequency::WordFrequency()
{
    map = new WordFreqMap;
}

WordFrequency::~WordFrequency()
{
    map = nullptr;
    delete map;
}

void WordFrequency::ReadText(const char* filename)
{
    std::fstream file;
    file.open(filename, std::ios::in);
    if(!file.is_open())
    {
        std::cout << "Error! Unable to open '" << filename << "'"  << std::endl;
    }
    else
    {
        std::string s;
        std::string str;
        while(!file.eof())
        {
            std::getline(file, s);
            str += s + ' ';
        }
        str.pop_back(); //erase the last space
        std::istringstream iss(str);
        
        do{
            std::string sub;
            std::string newsub;
            iss >> sub;
            std::transform(sub.begin(), sub.end(),
                           sub.begin(), ::tolower); //make the character to lower case
            int len = sub.length();
            for(int i = 0; i < len; i++)
            {
                if(sub[i] > 96 && sub[i] < 123) //only if it is low case alphabet, store it.
                    newsub += sub[i];
                else    //think all non alphabetic letter as delimiter. Then stores the letters before it came out to the hash map, and it clears the buffer so that the letters come out next to it can be stored again.
                {
                    if(newsub.length()>0)   //only cares if the letters' length is bigger than zero
                    {
                        IncreaseFrequency(newsub);
                        newsub.clear();
                    }
                }
                
            }
            if(newsub.length() > 0)
                IncreaseFrequency(newsub);
        }while(iss);
    }
}

int WordFrequency::GetFrequency(const std::string word)
{
    WordFreqElem* is_freq;
    is_freq = map->WordFreqMap::find(word);
    if(is_freq != NULL)
    {
        int freq = 0;
        freq = is_freq->val;
        return freq;
    }
    else
    {
        return 0;
    }
}

void WordFrequency::IncreaseFrequency(const std::string word)
{
    if(GetFrequency(word) != 0) //as GetFrequency function returns zero or the int values, we only need to check its frequency is whether zero or else.
    {
        int freq = 0;
        freq = this->map->WordFreqMap::find(word)->val;
        freq++;
        map->WordFreqMap::insert(word, freq);
    }
    else
    {
        map->WordFreqMap::insert(word, 1);
    }
    
}
