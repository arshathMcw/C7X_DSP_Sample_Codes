#include<iostream>
#include<bits/stdc++.h>
using namespace std;
void generate_random_value_for_2d_vector(vector<vector<int>>& vec){
    srand(time(0));
    for(vector<int>& arr : vec){
        for(int &val : arr){
            val = rand() / 100000000;
        }
    }
}
void generate_random_value_for_3d_vector(vector<vector<vector<int>>>& cube){
    srand(time(0));
    for(vector<vector<int>> &vec : cube){
        for(vector<int> &arr : vec){
            for(int &val : arr){
                val = rand() / 100000000;
            }
        }
    }
}
void convert_2d_to_1d(int row,int col,vector<vector<int>>& vec,vector<int>& res){
    for(int r=0;r < row;r++){
        for(int c=0;c < col;c++){
            res[r * col + c] = vec[r][c];
        }
    }
}
void convert_3d_to_1d(int row,int col,int depth,vector<vector<vector<int>>> vec,vector<int> &res){
    for(int r=0;r < row;r++){
        for(int c=0;c < col;c++){
            for(int d = 0;d < depth;d++){
                res[d+depth*(c+col*r)] = vec[r][c][d]; 
            }
        }
    }
}
void print_1d_vector(vector<int> res){
    for(int val : res){
        cout<<val<<" ";
    }
    cout<<endl;
}
void print_2d_vector(vector<vector<int>> vec){
    for(vector<int> arr : vec){
        for(int val : arr){
            cout<<val<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void print_3d_vector(int row,int col,int depth,vector<vector<vector<int>>> cube){
    for(vector<vector<int>> vec : cube){
        for(vector<int> arr : vec){
            for(int val : arr){
                cout<<val<<" ";
            }
            cout<<endl;
        }
    }
}
int main(){
    cout<<"Welcome to the Dimension convertor code \nHere we can convert 2D into 1D and 3D into 1D , it will we helpful when we do vectorization"<<endl;
    cout<<"\tChoices List\n1. 2 Dimensional to 1 Dimensional\n2. 3 Dimensional to 1 Dimensional"<<endl;
    int ch = 0,row,col,depth,result_size;
    while(ch < 1 || ch > 2){
        cout<<"Enter Your Choice (1/2): ";
        cin>>ch;
        if(ch < 1 || ch > 2) cout<<"Your Choice is Not Valid ... "<<endl;
    }
    if(ch == 1){
        cout<<"Enter the Row Size : ";
        cin>>row;
        cout<<"Enter the Column Size : ";
        cin>>col;
        vector<vector<int>> vector_2d(row,vector<int>(col,0));
        generate_random_value_for_2d_vector(vector_2d);
        result_size = row * col ;
        vector<int> result(result_size,0);
        convert_2d_to_1d(row,col,vector_2d,result);
        print_1d_vector(result);
    }
    else if(ch == 2){
        cout<<"Enter the Row Size : ";
        cin>>row;
        cout<<"Enter the Column Size : ";
        cin>>col;
        cout<<"Enter the Depth Size : ";
        cin>>depth;
        vector<vector<vector<int>>> vector_3d(row, vector<vector<int>>(col, vector<int>(depth, 0)));
        generate_random_value_for_3d_vector(vector_3d);
        result_size = row * col * depth;
        vector<int> result(result_size,0);
        convert_3d_to_1d(row,col,depth,vector_3d,result);
        print_1d_vector(result);
    }
}
