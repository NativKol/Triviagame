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
    /// Interaction logic for SearchRoom.xaml
    /// </summary>
    public partial class SearchRoom : Page
    {
        string req;
        string answer;
        int id = 0;
        string tags;
        string _ID;
        string _NAME;

        Communicator c = new Communicator();

        private void Room_Clicked(object sender, RoutedEventArgs e)
        {
            var myValue = ((Button)sender).Tag;
            _ID = (string)myValue;
            _NAME = _ID.Substring(2);
            _ID = _ID.Substring(0, 2);
            id = Int32.Parse(_ID);

            GetPlayersInRoomRequest log = new GetPlayersInRoomRequest { id = id };
            req = c.getPlayersSe(log);
            answer = c.getData(req);
            MessageBox.Show(answer);
        }

        public SearchRoom(Communicator comm)
        {
            InitializeComponent();
            c = comm;
            req = c.GetRooms();
            //MessageBox.Show(req);
            answer = c.getData(req);
            //MessageBox.Show(answer);
            List<string> result = answer.Split('"')
                    .Select((element, index) => index % 2 == 0  // If even index
                                          ? element.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)  // Split the item
                                          : new string[] { element })  // Keep the entire item
                    .SelectMany(element => element).ToList();

            List<Button> items = new List<Button>();
            for (int i = 5; i < result.ToArray().Length; i += 6)
            {
                tags = "";
                _ID = result[i - 3].Remove(0, 1);
                _ID = _ID.Remove(_ID.Length - 1);
                _NAME = result[i];
                var btn1 = new Button { Content = _NAME };
                btn1.FontSize = 18;
                btn1.Click += Room_Clicked;
                tags += _ID;
                tags += _NAME;
                btn1.Tag = tags;
                items.Add(btn1);
            }
            RoomsList.ItemsSource = items;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.GoBack();
        }

        private void Refresh(object sender, RoutedEventArgs e)
        {
            SearchRoom here = new SearchRoom(c);
            this.NavigationService.Navigate(here);
        }

        private void JoinRoom(object sender, RoutedEventArgs e)
        {
            if (id == 0)
                MessageBox.Show("Select Room");
            else
            {
                JoinRoomRequest logJ = new JoinRoomRequest { id = id };
                req = c.JoinRoomSe(logJ);
                //MessageBox.Show(req);
                if (!(c.handleCommunicate(req)))
                {
                    MessageBox.Show("The Romm Is Full!");
                }
                else
                {
                    RoomJoin RoomPage = new RoomJoin(c, id, _NAME);
                    this.NavigationService.Navigate(RoomPage);
                }
            }
        }
    }
}
