/*
 * This code Developed by Talal Alhammami
 * 16.06.2019 19:25 Uhr
 * Singen / Germany
 * 
 * */
#include <iostream>
#include <map>
#include <limits>
using namespace std;

template<typename K, typename V>
class interval_map {
	std::map <K,V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    //    std::cout << "Applying Constructor " << endl;

    }
   
    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {

			if (!(keyBegin < keyEnd)){
				return;
			}
			std::pair<K,V> n_Key_begin;    
			std::pair<K,V> n_Key_end;
			std::map<K,V>added_map;
			
			bool Begin_Extra_keys = false;
            bool end_Extra_keys = false;

			typename std::map<K,V>::iterator iter_Begin;
			iter_Begin = m_map.lower_bound(keyBegin);
			
			if ( iter_Begin != m_map.end() && keyBegin < iter_Begin->first ) 
			{
				
				if (iter_Begin != m_map.begin())
				{
					Begin_Extra_keys = true;
					--iter_Begin;
					n_Key_begin = std::make_pair(iter_Begin->first, iter_Begin->second);
			//		added_map.insert(n_Key_begin,n_Key_end);
              //      std::cout << " Checking the Extra Value :" << endl;
                //    std::cout << n_Key_begin.first << n_Key_begin.second << endl;
				}
			}

			typename std::map<K,V>::iterator iter_End;
			iter_End = m_map.lower_bound(keyEnd);
			
			if ( iter_End != m_map.end() && keyEnd < iter_End->first ) 
			{
				end_Extra_keys = true;
				typename std::map<K,V>::iterator Iter_ator = iter_End;
				--Iter_ator;
				n_Key_end = std::make_pair(keyEnd, Iter_ator->second);

			}

          
			bool ins_middle_Value = true;
			if (Begin_Extra_keys)
			{
				if (n_Key_begin.second == val)
					ins_middle_Value = false;
			}
			else {
				if (iter_Begin != m_map.begin()) 
				{
					typename std::map<K,V>::iterator before_middle_Value = iter_Begin;
					--before_middle_Value;
					if (before_middle_Value->second == val)
						ins_middle_Value = false;
				}
			}



			if (end_Extra_keys)
            {
				if ( (ins_middle_Value && n_Key_end.second == val) || (!ins_middle_Value && n_Key_end.second == n_Key_begin.second) )
					end_Extra_keys = false;
			} else {
				if ( (ins_middle_Value && iter_End!=m_map.end() && iter_End->second == val) || (!ins_middle_Value && iter_End!=m_map.end() && iter_End->second == n_Key_begin.second) )
					iter_End = m_map.erase(iter_End);
			}

			iter_Begin = m_map.erase(iter_Begin, iter_End);
			if (Begin_Extra_keys)
				iter_Begin = m_map.insert(iter_Begin, n_Key_begin);
			if (ins_middle_Value)
				iter_Begin = m_map.insert(iter_Begin, std::make_pair(keyBegin, val));
			if (end_Extra_keys)
                m_map.insert(iter_Begin, n_Key_end);
              
    }   

    // testing Function 
	void test_interval_map() {
		m_map.insert(std::make_pair(1, 'A'));
		m_map.insert(std::make_pair(3, 'B'));
		m_map.insert(std::make_pair(8, 'D'));
		m_map.insert(std::make_pair(10, 'E'));
        m_map.insert(std::make_pair(13, 'D'));
        m_map.insert(std::make_pair(14, 'E'));
		m_map.insert(std::make_pair(18, 'A'));
	}
    
  // print Function for Debugging           
void print_map() {
    std::cout << " Printing  Mapping OuT_PuT : " << std::endl;
    for(auto entry : m_map) {
        std::cout << entry.first << "\t -> " << entry.second << std::endl;
    }
}

// INSERT YOUR SOLUTION HERE
    

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
};

int main()
{
interval_map<unsigned int, char> Think_Cell_Map {'A'};  
cout << "**************************************************"<< endl;
cout << "**************************************************"<< endl;
cout << "***  Test assignment Think-Cell C++ Develover  ***"<< endl;
cout << "*** \t \t                \t       ***"<< endl;
cout << "*** \t \tTalal Alhammami \t       ***"<< endl;
cout << "*** \t \t 16.06.2019     \t       ***"<< endl;
cout << "*** \t \t  19:25 Uhr     \t       ***"<< endl;
cout << "***  Test assignment Think-Cell C++ Develover  ***"<< endl;
cout << "**************************************************"<< endl;
cout << "**************************************************"<< endl;
	Think_Cell_Map.test_interval_map();
    cout << endl;
	Think_Cell_Map.print_map();
    cout << endl;
    cout << endl;
	Think_Cell_Map.assign(1, 4, 'A');
	Think_Cell_Map.assign(5, 7, 'B');
	Think_Cell_Map.assign(6, 8, 'D');
	Think_Cell_Map.assign(8, 11, 'E');
    Think_Cell_Map.assign(11, 15, 'A');
    cout << endl;
    cout << endl;
	Think_Cell_Map.print_map();
    cout << endl;
    return 0;

}
