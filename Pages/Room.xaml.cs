using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
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
    /// Interaction logic for Room.xaml
    /// </summary>
    public partial class Room : Page
    {
        string req;
        string answer;
        string adminName = "##";
        Communicator c;
        Dictionary <string, Label> items = new Dictionary<string, Label>();
        private BackgroundWorker background_worker = new BackgroundWorker();
        string[] _names = new string[9];

        void background_worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
            {
                MessageBox.Show("BackgroundWorker canceled");
            }
            else
            {
                //MessageBox.Show("BackgroundWorker ended successfully");
            }
        }


        void background_worker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            int i = 0;
            while (i < _names.Length)
            {
                var user = new Label { Content = _names[i] };
                user.FontSize = 18;
                if (user.Content != null)
                {
                    if (!(items.ContainsKey((string)user.Content)))
                    {
                        Players_List.Items.Add(user);
                        items.Add((string)user.Content, user);
                    }
                }
                i++;
            }
            foreach (var item in items.Values.ToList())
            {
                if (!(_names.Contains(item.Content)))
                {
                    Players_List.Items.Remove(item);
                    items.Remove((string)item.Content);
                }
            }
        }


        void updateData(object sender, DoWorkEventArgs e)
        {
            Thread.Sleep(3000);        //wait 3 sec..
            int i = 0;
            int j = 0;
            while (true)
            {
                i = 0;
                j = 0;
                if (background_worker.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }
                answer = c.getData(req);
                //MessageBox.Show(answer);
                List<string> result = answer.Split('"')
                    .Select((element, index) => index % 2 == 0  // If even index
                                  ? element.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)  // Split the item
                                  : new string[] { element })  // Keep the entire item
                    .SelectMany(element => element).ToList();

                adminName = result[0];

                if (result.Count() >= 22)
                {
                    e.Cancel = true;
                    break;
                }

                while (i < result.Count())
                {
                    _names[j] = result[i];
                    i += 2;
                    j++;
                }
                while (j < 9)
                {
                    _names[j] = null;
                    j++;
                }
                //Players_List.ItemsSource = items;
                background_worker.ReportProgress(_names.Length);
                Thread.Sleep(3000);        //wait 10 sec..
            }

        }

        public Room(Communicator comm, int id, string roomName, int players, int questions, int time)
        {
            InitializeComponent();
            c = comm;

            _roomName.Content = roomName;
            _players.Content = players;
            _questions.Content = questions;
            _time.Content = time;

            /*
               PARTICIPANTS LIST   
            */

            GetPlayersInRoomRequest log = new GetPlayersInRoomRequest { id = id };
            req = c.getPlayersAdminSe(log);
            //MessageBox.Show(req);


            //Thread ts1 = new Thread(updateData);
            //ts1.SetApartmentState(ApartmentState.STA);
            //ts1.Start();
            background_worker.ProgressChanged += background_worker_ProgressChanged;
            background_worker.DoWork += updateData;
            background_worker.RunWorkerCompleted += background_worker_RunWorkerCompleted;

            background_worker.RunWorkerAsync();
            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            /*
             CLOSE ROOM REQUEST
             */
            string request = c.CloseRoomSe();
            //MessageBox.Show(request);
            string _get = c.getData(request);
            this.NavigationService.GoBack();
        }
    }
}
