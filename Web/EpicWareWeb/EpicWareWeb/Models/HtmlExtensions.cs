using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace EpicWareWeb.Models
{
    public static class HtmlExtensions
    {

        public static string TagCloud(this HtmlHelper helper)
        {
            var output = new System.Text.StringBuilder();
            output.Append(@"<div class=""TagCloud"">");
            using(var model = new EventsEntities())
            {
                TagCloudCounter tagCloud = model.GetTagCloud();
                foreach (TagCloud tag in tagCloud.TagClouds)
                {
                    output.AppendFormat(@"<div class=""tag{0}"">",
                                        tagCloud.GetRankForTag(tag));
                    output.Append(tag.Tag);
                    output.Append("</div>");
                }
            }
            output.Append("</div>");
            return output.ToString();
        }
    }
}