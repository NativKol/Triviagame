using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TriviaGraphic
{
    /// <summary>
    /// Interaction logic for Records.xaml
    /// </summary>
    public partial class Records : Page
    {
        Communicator c;
        string req;
        string answer;

        public Records(Communicator comm)
        {
            InitializeComponent();
            this.c = comm;
            req = c.RecordsSe();
            //MessageBox.Show(req);
            answer = c.getData(req);
            //MessageBox.Show(answer);

            var result = answer.Split('"')
                     .Select((element, index) => index % 2 == 0  // If even index
                                           ? element.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)  // Split the item
                                           : new string[] { element })  // Keep the entire item
                     .SelectMany(element => element).ToList();

            First.Content = result[0];
            Second.Content = result[2];
            Third.Content = result[4];
            
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.GoBack();
        }
    }
}
