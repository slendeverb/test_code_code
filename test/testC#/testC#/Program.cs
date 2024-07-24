namespace testcsharp
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            FileStream inputStream = new FileStream("../../in.txt", FileMode.Open, FileAccess.Read);
            FileStream outputStream = new FileStream("../../out.txt", FileMode.Truncate, FileAccess.Write);
            StreamReader input = new StreamReader(inputStream);
            StreamWriter output = new StreamWriter(outputStream);
            TextReader oldIn = Console.In; TextWriter oldOut = Console.Out;
            Console.SetIn(input); Console.SetOut(output);
            int T = Convert.ToInt32(Console.ReadLine());
            while (T-- != 0)
            {
                Solve();
            }
            Console.SetIn(oldIn); Console.SetOut(oldOut);
            input.Close(); output.Close();
            inputStream.Close(); outputStream.Close();
        }

        internal static readonly char[] separator = [' '];

        public static void Solve()
        {
            int n = Convert.ToInt32(Console.ReadLine());
            var arr1 = Console.ReadLine().Split(separator).Where(item => !string.IsNullOrEmpty(item)).ToArray();
            foreach (var item in arr1)
            {
                Console.Write(item + " ");
            }
            Console.WriteLine();

            int m = Convert.ToInt32(Console.ReadLine());
            var arr2 = Console.ReadLine().Split(separator).Where(item => !string.IsNullOrEmpty(item)).ToArray();
            foreach (var item in arr2)
            {
                Console.Write(item + " ");
            }
            Console.WriteLine();
        }
    }
}
