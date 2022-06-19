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
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Page
    {
        Communicator c;
        string req;
        string answer;

        public Statistics(Communicator comm)
        {
            InitializeComponent();
            this.c = comm;
            req = c.StatsSe();
            //MessageBox.Show(req);
            answer = c.getData(req);
            //MessageBox.Show(answer);

            var result = answer.Split('"')
                     .Select((element, index) => index % 2 == 0  // If even index
                                           ? element.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)  // Split the item
                                           : new string[] { element })  // Keep the entire item
                     .SelectMany(element => element).ToList();

            GamesPlayed.Content = result[0];
            Correct.Content = result[2];
            int notCorrect = Int32.Parse(result[4]) - Int32.Parse(result[2]);
            Wrong.Content = notCorrect.ToString();
            AvarageTime.Content = result[6];
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.GoBack();
        }
    }
}
