namespace testcsharp2
{
    class Program
    {
        public static void Main(string[] args)
        {
            string[] ideas = ["coffee", "donuts", "time", "toffee"];
            Console.WriteLine(new Solution().DistinctNames(ideas));
        }
    }

    class Solution
    {
        public long DistinctNames(string[] ideas)
        {
            HashSet<string>[] groups = new HashSet<string>[26];
            for (int i = 0; i < groups.Length; i++)
            {
                groups[i] = new HashSet<string>();
            }
            foreach (var s in ideas)
            {
                groups[s[0] - 'a'].Add(s[1..]);
            }

            long res = 0;
            for (int i = 1; i < 26; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    long m = groups[i].Where(s => groups[j].Contains(s)).Count();
                    res += (groups[i].Count - m) * (groups[j].Count - m);
                }
            }
            return res * 2;
        }
    }
}