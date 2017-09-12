using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace contest
{

class Program
{
    static void Main(string[] args)
    {
        var parts = Console.ReadLine().Split(' ');
        var a = Int32.Parse(parts[0]);
        var b = Int32.Parse(parts[1]);

        Console.Write(a + b);
    }
}

}
