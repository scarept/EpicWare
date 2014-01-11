using EpicWareWeb.DAL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public partial class EventRelationsEntities : IDisposable
        {

            private List<string> ListTags()
            {
                DataContext db = new DataContext();
                List<string> newListTags = new List<string>();
                foreach (TagConnection tag in db.tagConnections)
                {
                    newListTags.Add(tag.tag);
                }

                return newListTags;
            }

            public TagCloudCounter GetTagCloud()
            {

                var tagCloudCount = new TagCloudCounter();
                tagCloudCount.EventsCount = ListTags().Count();

                List<TagCloud> list = new List<TagCloud>();

                List<string> list_sort = ListTags().Distinct().ToList();

                for(int i=0;i<list_sort.Count();i++){
                    TagCloud t = new TagCloud();
                    string s = list_sort.ElementAt(i).ToString();
                    t.Tag = s;
                    int count=0;
                    for(int j=0;j<ListTags().Count();j++){
                        if(s==ListTags().ElementAt(j).ToString()){
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