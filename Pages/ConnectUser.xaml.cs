using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
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
    /// Interaction logic for ConnectUser.xaml
    /// </summary>
    /// 
    public partial class ConnectUser : Page 
    {
        string username;
        string password;
        string req;
        Communicator c = new Communicator();

        public ConnectUser()
        {
            InitializeComponent();
        }

        private void login_click(object sender, RoutedEventArgs e)
        {
            username = UsernameInput.Text;
            password = PasswordInput.Password;
            Console.WriteLine(username + " " + password);
            LoginRequest log = new LoginRequest { username = username, password = password };
            
            req = c.LoginSe(log);
            //MessageBox.Show(req);
            if (c.handleCommunicate(req))
            {
                //MessageBox.Show(username + " " + password);
                c.setName(username);
                Home HomePage = new Home(c);
                this.NavigationService.Navigate(HomePage);  
            }
            else
            {
                MessageBox.Show("User Does Not Exist!");
            }
        }

        private void signup_click(object sender, RoutedEventArgs e)
        {

            Register registerPage = new Register(c);
            this.NavigationService.Navigate(registerPage);
        }
    }
}
