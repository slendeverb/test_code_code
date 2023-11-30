namespace testcsharp
{
    internal class Program
    {
        static void Main(string[] args)
        {
            FileStream inStream = null, outStream = null;
            StreamReader inReader = null;
            StreamWriter outWriter = null;
            TextReader oldIn = Console.In;
            TextWriter oldOut = Console.Out;

            try
            {
                inStream = new FileStream("C:/Users/slendeverb/Documents/code_code/test/in.txt", FileMode.Open, FileAccess.Read);
                inReader = new StreamReader(inStream);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            Console.SetIn(inReader);

            try
            {
                outStream = new FileStream("C:/Users/slendeverb/Documents/code_code/test/out.txt", FileMode.Truncate, FileAccess.Write);
                outWriter = new StreamWriter(outStream);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            Console.SetOut(outWriter);

            int T = Convert.ToInt32(Console.ReadLine());
            while (T-- != 0)
            {
                Solve();
            }
            inReader.Close();
            outWriter.Close();
            inStream.Close();
            outStream.Close();
            Console.SetIn(oldIn);
            Console.SetOut(oldOut);
        }

        static void Solve()
        {
            int n = Convert.ToInt32(Console.ReadLine());
            string input = Console.ReadLine();
            var arr1 = input.Split(new char[] { ' ', ',' }).Where(items => !string.IsNullOrEmpty(items)).ToList();
            foreach (var item in arr1)
            {
                Console.Write(item.ToString() + " ");
            }
            Console.WriteLine();

            int m = Convert.ToInt32(Console.ReadLine());
            input = Console.ReadLine();
            var arr2 = input.Split(new char[] { ' ', ',' }).Where(items => !string.IsNullOrEmpty(items)).ToList();
            foreach (var item in arr2)
            {
                Console.Write(item.ToString() + " ");
            }
            Console.WriteLine();
        }
    }
}
