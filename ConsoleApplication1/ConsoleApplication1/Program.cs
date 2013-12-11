static void Main()
{
    int x = 5;
    int y = x;
     
    string s = "Hello";
    s = "Goodbye";
     
    MyInt a = new MyInt();
    a.value = 10;
     
    MyInt b = a;
    b.value = y;
     
    Console.WriteLine(a.value);
     
    Test(a);   
    Console.WriteLine(a.value);
     
    Test2(ref a);  
    Console.WriteLine(a.value);
}
 
class MyInt
{
    public int value;
}
 
void Test(MyInt num)
{
    num.value = 25;
    num = null;
}
 
void Test2(ref MyInt num)
{
    num.value = 30;
    num = null;
}
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
        }
    }
}
