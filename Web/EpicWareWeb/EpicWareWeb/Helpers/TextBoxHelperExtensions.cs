using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Web;
using System.Web.Mvc;
using System.Web.Mvc.Html;

namespace System.Web.Mvc.Html 
{
    public static class TextBoxHelperExtensions
    {
        /// <summary>  
        /// Retorna o elemento input do tipo text com calendário  
        /// </summary>  
        public static MvcHtmlString TextBoxDatePickerFor<TModel, TProperty>(this HtmlHelper<TModel> htmlHelper, Expression<Func<TModel, TProperty>> expression)
          where TModel : class
        {
            /* 
            Extrai metadados da expressão lambda passada (ex: model => model. 
            DataNascimento), onde precisamos do nome e valor da propriedade 
            */
            ModelMetadata metadados = ModelMetadata.FromLambdaExpression(expression, htmlHelper.ViewData);

            /* 
            Valor obtido no metadados para que possamos  
            formata-los, senão mostraria a hora junto com a data. 
            */
            DateTime? data = (metadados.Model as DateTime?);

            /* 
            Chama o helper TextBox do próprio .NET passando o nome da  
            propriedade, e retornando o valor da data no formato  
            dd/MM/yyyy e atribuindo a classe "datePicker" no input que  
            será retornado para a view. 
            */
            return htmlHelper.TextBox(
                metadados.PropertyName,
                data != null && data != default(DateTime) ? data.Value.ToString("dd/MM/yyyy") : string.Empty,
                new { @class = "datePicker" });
        }
    }  
}