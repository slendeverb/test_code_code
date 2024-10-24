namespace testcsharp2
{
    class Program
    {
        public static void Main(string[] args)
        {
            DateTime start= DateTime.Now;
            for(int i=0;i<1_0000_0;i++){
                Console.WriteLine(i);
            }
            DateTime end= DateTime.Now;
            Console.WriteLine(end-start);
        }
    }
}