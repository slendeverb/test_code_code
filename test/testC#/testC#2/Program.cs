namespace testcsharp2
{
    class Program
    {
        public static void Main(string[] args)
        {
            string[] strings = ["a", "你", "🤣"];
            Act(strings);
        }

        public static void Act(string[] strings)
        {
            foreach (var s in strings)
            {
                Console.WriteLine(s);
                Print(s.ToCharArray());
                Print(System.Text.Encoding.UTF8.GetBytes(s));
            }
        }

        public static void Print(char[] charArray)
        {
            foreach (var ch in charArray)
            {
                Console.Write(Convert.ToString(ch, 2).PadLeft(8, '0'));
                Console.Write(" ");
            }
            Console.WriteLine();
        }

        public static void Print(byte[] byteArray)
        {
            foreach (var b in byteArray)
            {
                Console.Write(Convert.ToString(b, 2).PadLeft(8, '0'));
                Console.Write(" ");
            }
            Console.WriteLine();
        }
    }
}