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
    /// Interaction logic for Home.xaml
    /// </summary>
    public partial class Home : Page
    {
        Communicator c;

        public Home(Communicator comm)
        {
            InitializeComponent();
            this.c = comm;
            helloUSer.Content = "Hello,\n" + c.getName();
        }

        private void Create_Room_Click(object sender, RoutedEventArgs e)
        {
            Create_Room CreateRoomPage = new Create_Room(c);
            this.NavigationService.Navigate(CreateRoomPage);
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Content = null;
        }

        private void stats_Click(object sender, RoutedEventArgs e)
        {
            Statistics StatisticsPage = new Statistics(this.c);
            this.NavigationService.Navigate(StatisticsPage);
        }

        private void records_click(object sender, RoutedEventArgs e)
        {
            Records RecordsPage = new Records(c);
            this.NavigationService.Navigate(RecordsPage);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void join_room(object sender, RoutedEventArgs e)
        {
            SearchRoom joinRoomPage = new SearchRoom(c);
            this.NavigationService.Navigate(joinRoomPage);
        }
    }
}
