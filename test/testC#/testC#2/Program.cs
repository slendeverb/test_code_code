using System.Numerics;

namespace testcsharp2
{
    class Program
    {
        public static void Main(string[] args)
        {
            var start = DateTime.Now;
            BigInteger bigInteger = BigInteger.Parse("1");
            Console.WriteLine(bigInteger << 100_0000);
            var end = DateTime.Now;
            Console.WriteLine(end - start);
        }
    }
}