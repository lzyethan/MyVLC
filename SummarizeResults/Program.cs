﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace SummarizeResults
{
    class Program
    {
        static void summarize(string type)
        {
            string[]files = Directory.GetFiles(Environment.CurrentDirectory,"*." + type + ".txt",SearchOption.TopDirectoryOnly);
            StreamWriter sw = new StreamWriter(type + ".csv");
            Dictionary<string, List<double>> avgDic = new Dictionary<string, List<double>>();
            if (type == "mp4")
            {
                sw.WriteLine("file name, original file name, original length, test length, LCS, accuracy");
            }
            else
            {
                sw.WriteLine("file name, original length, test length, LCS, accuracy");
            }
            foreach (string file in files)
            {
                StreamReader sr = new StreamReader(file);
                string data;
                if (!sr.EndOfStream)
                {
                    data = "";
                    while (!data.Contains(" and "))
                    {
                        data = sr.ReadLine();
                    } 
                    Regex reg = new Regex(@"\d+ and \d+");
                    Match match = reg.Match(data);
                    string[] total = match.Value.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    int orig, tst, lcs;
                    orig = int.Parse(total[0]);
                    tst = int.Parse(total[2]);
                    while (!data.Contains("Longest Common SubString"))
                    {
                        data = sr.ReadLine();
                    } 
                    reg = new Regex(@"Length = \d+");
                    match = reg.Match(data);
                    string[] common = match.Value.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    lcs = int.Parse(common[2]);
                    string name = (new FileInfo(file)).Name;
                    double accuracy = ((double)lcs) / orig;
                    if (type == "mp4")
                    {
                        int ind = name.IndexOf('_');
                        ind = name.IndexOf('_', ind+1);
                        string orig_name = name.Substring(ind + 1);
                        if(!avgDic.ContainsKey(orig_name))
                        {
                            avgDic.Add(orig_name, new List<double>());
                        }
                        avgDic[orig_name].Add(accuracy);
                        sw.WriteLine("{0}, {5}, {1}, {2}, {3}, {4}", name.Substring(0, ind), orig, tst, lcs, accuracy, orig_name);
                    }
                    else
                    {
                        sw.WriteLine("{0}, {1}, {2}, {3}, {4}", name, orig, tst, lcs, accuracy);
                    }
                }
                sr.Close();
            }
            sw.Close();
            if (type == "mp4")
            {
                // write averages
                sw = new StreamWriter("avg_mp4.csv");
                sw.WriteLine("original file name, Number of Runs, Average Accuracy");
                foreach(string key in avgDic.Keys)
                {
                    sw.WriteLine("{0}, {1}, {2}", key, avgDic[key].Count,  avgDic[key].Average());
                }
                sw.Close();
            }
        }
        static void Main(string[] args)
        {
            summarize("mp4");
            summarize("avi");
        }
    }
}
