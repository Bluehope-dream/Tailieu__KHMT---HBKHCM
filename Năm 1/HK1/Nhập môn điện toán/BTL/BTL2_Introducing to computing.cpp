#include<cmath>
#include<iostream>
#include<string>
using namespace std;
int move(string moves);
bool primality(int n)
{   int k;
    for (int i=1;i<=n;i++){
    if (n%i==0) k++;
         }
    if(k!=2) return false; 
    return true;
}
bool squared(int n)
{  int check;
   check= sqrt(n);
   return ( check*check == n );
}
int main()
{
  string moves;
  cin>>moves;
  int x = 0, y = 0;
   for ( size_t i = 0; i < moves.size(); i+=2) {
        char step_test = moves[i];
         int steps = moves[i+1] - '0';
         switch (step_test) {
            case 'U': 
            y += steps; 
            break;
            case 'D': 
            y -= steps; 
            break;
            case 'L': 
            x -= steps;
            break;
            case 'R': 
            x += steps; 
            break;
        }
   }
       int distance = round(sqrt(x * x + y * y));
    
    cout<<"The distance the vehicle has moved from the origin to the current point is: "<< distance <<"\n";
if(primality(distance)){
   cout <<"Number "<<distance<<" is prime number\n";
}
if(squared(distance)){
cout<<"Number "<<distance<<" is square number\n";
}
return 0;
}