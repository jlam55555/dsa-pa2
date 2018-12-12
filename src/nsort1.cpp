void sortRandInts(list<Data *> &l) {
    struct dataWrapper {
        unsigned int myInt;
        Data * myDataPtr;
    };
    
    vector<dataWrapper> objVector(1010000);
    vector<dataWrapper>::iterator vIter = objVector.begin();
    
    list<Data *>::iterator lIter = l.begin();       
    while (lIter != l.end()) {
            struct dataWrapper tempStruct;
            tempStruct.myInt = (*lIter)->val2;
            tempStruct.myDataPtr = *lIter;
            //cout << tempStruct.myInt << endl;
            
            *vIter = tempStruct;
            ++lIter;
            ++vIter;
        }
    
    std::stable_sort(objVector.begin(), vIter, [] (struct dataWrapper d1, struct dataWrapper d2) {
        return d1.myInt < d2.myInt;
    } );
    
    vIter = objVector.begin();
    lIter = l.begin();
    while (lIter != l.end()) {
            (*lIter) = vIter->myDataPtr;
            //cout << (*lIter)->val2 << endl;
            ++lIter;
            ++vIter;
        }
}
