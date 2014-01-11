using EpicWareWeb.DAL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public partial class UserRelationsEntities : IDisposable
    {

        private List<string> ListTags(int id)
        {
            DataContext db = new DataContext();
            List<string> newListTags = new List<string>();
            foreach (Connection conn in db.users.Find(id).listConnections)
            {
                newListTags.Add(conn.tagConnection.tag);
            }

            return newListTags;
        }

        public TagCloudCounter GetTagCloud(int id)
        {

            var tagCloudCount = new TagCloudCounter();
            tagCloudCount.EventsCount = ListTags(id).Count();

            List<TagCloud> list = new List<TagCloud>();

            List<string> list_sort = ListTags(id).Distinct().ToList();

            for (int i = 0; i < list_sort.Count(); i++)
            {
                TagCloud t = new TagCloud();
                string s = list_sort.ElementAt(i).ToString();
                t.Tag = s;
                int count = 0;
                for (int j = 0; j < ListTags(id).Count(); j++)
                {
                    if (s == ListTags(id).ElementAt(j).ToString())
                    {
                        count++;
                    }
                }
                t.Count = count;
                list.Add(t);
            }

            tagCloudCount.TagClouds = list;

            return tagCloudCount;

        }

        public void Dispose()
        {
        }

    }
}