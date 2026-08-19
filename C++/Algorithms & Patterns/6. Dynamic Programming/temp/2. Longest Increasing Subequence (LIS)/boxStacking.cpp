#include <bits/stdc++.h>
using namespace std;

/*
    Recurrence Relation:
    -------------------

    MSH(i) = Maximum possible Stack Height with box i at top of stack
                            ______
                            | i  |
                        --------------
                        |     j      |
                        --------------

    MSH(i) = {max(MSH(j)) + height(i)}   where j<i and baseArea(j) > baseArea(i)
    If there is no such j then MSH(i) = height(i)

    Algorithm:
        1) Generate all 3 rotations of all boxes. The size of rotation array becomes 3 times the size of original array. For simplicity, we consider depth as always smaller than or equal to width.

        2) Sort the above generated 3n boxes in decreasing order of base area.

        3) After sorting the boxes, the problem is same as LIS with following optimal substructure property.
            MSH(i) = {max(MSH(j)) + height(i)}   where j<i and baseArea(j) > baseArea(i)
                     If there is no such j then MSH(i) = height(i)
            At each step we see if box j can be included or not. Conditions:
                box i can be placed on top of box j i.e. length and width of box i is less than that of box j. 
                if yes then we can add it to the max height if the MSH[j] + height of i > MSH[i] 
    
    Time Complexity: O(n2)

*/

struct Box{
    int l, w, h;
};


class comp{
    public:
        bool operator()(Box &a, Box &b){
            int baseAreaA = a.l * a.w;
            int baseAreaB = b.l * b.w;

            if(baseAreaA < baseAreaB)
                return false;
            return true;
        }
};

class Solution
{
    public:
        int findMaxStackHeight(vector<Box> boxes){
            if(boxes.size()==0)
                return 0;
            
            int N = boxes.size();
            //Create an array to store all rotations of N boxes
            vector<Box> rotations;

            int index = 0;
            for(int i=0; i<N; i++){
                Box box = boxes[i];

                Box rotation1;
                rotation1.l = max(box.l, box.w);
                rotation1.w = min(box.l, box.w);
                rotation1.h = box.h;
                rotations.push_back(rotation1);

                Box rotation2;
                rotation2.l = max(box.l, box.h);
                rotation2.w = min(box.l, box.h);
                rotation2.h = box.w;
                rotations.push_back(rotation2);

                Box rotation3;
                rotation3.l = max(box.h, box.w);
                rotation3.w = min(box.h, box.w);
                rotation3.h = box.l;
                rotations.push_back(rotation3);
            }

            //sort the boxes on the basis of their baseArea in decreasing order.
            sort(rotations.begin(), rotations.end(), comp());
            
            /* Uncomment the following lines to view the rotations
            for(Box box: rotations)
                cout<<box.l<<" "<<box.w<<" "<<box.h<<endl;
            */
            
            
            //Now we have all the rotations of the boxes.
            //So our objective is to maximize the height keeping the base area decreasing as we go from bottom to up
            
            //Create a new vector MSH that will store the MSH(i) 
            //Initialize the vector with the height of i
            vector<int> MSH;
            vector<int> resultantBoxes;
            for(Box box: rotations){
                MSH.push_back(box.h);
            }

            for(int i=0; i<rotations.size(); i++)
                resultantBoxes.push_back(i);

            int maxHeight = MSH[0];
            int maxHeightIndex = 0;
            for(int i=1; i<rotations.size(); i++){
                for(int j=0; j<i; j++){
                
                    //can box at i go on top of box at j?
                    if(rotations[i].w < rotations[j].w && rotations[i].l < rotations[j].l){
                        
                        if(MSH[i] < MSH[j] + rotations[i].h){
                            MSH[i] = MSH[j] + rotations[i].h;
                            if(maxHeight < MSH[i]){
                                maxHeight = MSH[i];
                                maxHeightIndex = i;
                            }
                            resultantBoxes[i] = j;
                        }
                    }
                }
            }
            
            //print the boxes that will be stacked up in descendin order of baseArea
            cout<<"The following boxes will be stacked up: "<<endl;
            int i = maxHeightIndex;
            while(i>=0){
                cout<<rotations[i].l<<" "<<rotations[i].w<<" "<<rotations[i].h<<endl;
                if(i==0)
                    break;
                i = resultantBoxes[i];
            }
            
            return maxHeight;
        }        
};

int main(){
    Solution obj;
    vector<Box> boxes = {{1 ,2, 4}, {3, 2, 5}};
    
    int ans = obj.findMaxStackHeight(boxes);
    cout<<"Maximum height: "<<ans;
        
    return 0;
}

//Follow up problem: Box Stacking N boxes and K dimensions