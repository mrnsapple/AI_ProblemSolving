
#include <string>
#include <vector>
#include <iostream>
#ifndef NODEDATA_HPP
#define NODEDATA_HPP

namespace AI
{
    struct Variant
    {
        enum 
        {
            TYPE_CHAR,
            TYPE_INT,
            TYPE_DOUBLE, 
            TYPE_FLOAT,
            TYPE_BOOL,
            TYPE_STRING_ID // number of unique types
        }_type;

        union
        {
            char _asChar;
            int _asInt;
            double _asDouble;
            float _asFloat;
            bool _asBool;
            char _asString;
        };
    };
    class NodeData
    {
    public:
        int _size;
        std::vector<Variant> _data; 
        bool operator==(NodeData &other) 
        { 
        //    std::cout << "IN COMARE NODEDATA "<< std::endl;
            if (_size != other._size || _size != other._size)
                 return false;
            for (int i = 0; i <_size; i++) {
                 if (_data[i]._asInt != other._data[i]._asInt)
                     return false;
            }
            return true;
        }
        // bool operator!=(NodeData &other) 
        // { 
        // //    std::cout << "IN COMARE NODEDATA "<< std::endl;
        //     if (_size != other._size ||_size!= other._size)
        //          return true;
        //     for (int i = 0; i < _data.size(); i++) {
        //          if (_data[i]._asInt != other._data[i]._asInt)
        //              return true;
        //     }
        //     return false;
        // }

    };

}
#endif
        