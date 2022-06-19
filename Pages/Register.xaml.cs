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
    /// Interaction logic for Register.xaml
    /// </summary>
    public partial class Register : Page
    {
        Communicator c;
        string username;
        string password;
        string email;
        string req;

        public Register(Communicator comm)
        {
            InitializeComponent();
            this.c = comm;
        }

        private void signup_click(object sender, RoutedEventArgs e)
        {
            username = _Username.Text;
            password = _Password.Password;
            email = _Email.Text;

            SignupRequest log = new SignupRequest { username = username, password = password, email = email};

            req = c.RegisterSe(log);
            //MessageBox.Show(req);
            if (c.handleCommunicate(req))
            {
                Console.WriteLine(username + " " + password + " " + email);
                //MessageBox.Show(username + " " + password + " " + email);
                c.setName(username);
                Home HomePage = new Home(c);
                this.NavigationService.Navigate(HomePage);
            }
            else
            {
                MessageBox.Show("Username Already Taken");
            }
        }

        private void back_click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.GoBack();
        }
    }
}
