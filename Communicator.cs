using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//using Newtonsoft.Json;
//using System.Text.Json;
using System.Text.Json;
using System.Net.Sockets;
using System.Net;

namespace TriviaGraphic
{
    enum codes { Error_, signup_, login_, logout_, join_, create_, getRoom_, getPlayers_, getHighScore_, getPersonalStats_ };

    public struct SignupRequest
    {
        public string username { get; set; }
        public string password { get; set; }
        public string email { get; set; }
    };

    public struct LoginRequest
    {
        public string username { get; set; }
        public string password { get; set; }
    };

    public struct CreateRoomRequest
    {
        public string name { get; set; }
        public int max_users { get; set; }
        public int question_count { get; set; }
        public int answer_timeout { get; set; }
    };

    public struct GetPlayersInRoomRequest
    {
        public int id { get; set; }
    };

    public struct JoinRoomRequest
    {
        public int id { get; set; }
    };




    public class Communicator
    {
        NetworkStream _stream;
        string _name;

        public Communicator()
        {
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8826);
            client.Connect(serverEndPoint);
            NetworkStream clientStream = client.GetStream();
            this._stream = clientStream;
            byte[] buffer = new ASCIIEncoding().GetBytes("hello");
            this._stream.Write(buffer, 0, buffer.Length);
            this._stream.Flush();
            buffer = new byte[4096];
            int bytesRead = this._stream.Read(buffer, 0, 4096);
            var text = System.Text.Encoding.ASCII.GetString(buffer);

            Console.WriteLine(text);
        }

        public Communicator(NetworkStream stream)
        {
            this._stream = stream;
        }

        public void setName(string name)
        {
            this._name = name;
        }

        public string getName()
        {
            return this._name;
        }

        public NetworkStream getStream()
        {
            return this._stream;
        }

        public static string getBetween(string strSource, string strStart, string strEnd)
        {
            if (strSource.Contains(strStart) && strSource.Contains(strEnd))
            {
                int Start, End;
                Start = strSource.IndexOf(strStart, 0) + strStart.Length;
                End = strSource.IndexOf(strEnd, Start);
                return strSource.Substring(Start, End - Start);
            }

            return "";
        }

        public bool handleCommunicate(string req)
        {
            Console.WriteLine(req);
            byte[] buffer = new ASCIIEncoding().GetBytes(req);
           
            this._stream.Write(buffer, 0, buffer.Length);
            this._stream.Flush();
            buffer = new byte[4096];
            int bytesRead = this._stream.Read(buffer, 0, 4096);
            string text = System.Text.Encoding.ASCII.GetString(buffer);

            Console.WriteLine(text);

            text = getBetween(text, "{", "}");
            Console.WriteLine(text);
            char error = text[text.Length - 1];
            Console.WriteLine(error);
            if (error == '0')
                return false;
            return true;
        }

        public int getRoomID(string req)
        {
            Console.WriteLine(req);
            byte[] buffer = new ASCIIEncoding().GetBytes(req);

            this._stream.Write(buffer, 0, buffer.Length);
            this._stream.Flush();
            buffer = new byte[4096];
            int bytesRead = this._stream.Read(buffer, 0, 4096);
            string text = System.Text.Encoding.ASCII.GetString(buffer);

            Console.WriteLine(text);

            text = getBetween(text, "{", "}");
            Console.WriteLine(text);
            text = text.Substring(Math.Max(0, text.Length - 2)); ;
            Console.WriteLine(text);
            return Int32.Parse(text);
        }

        public string getData(string req)
        {
            Console.WriteLine(req);
            byte[] buffer = new ASCIIEncoding().GetBytes(req);
            this._stream.Write(buffer, 0, buffer.Length);
            this._stream.Flush();
            buffer = new byte[4096];
            int bytesRead = this._stream.Read(buffer, 0, 4096);
            string text = System.Text.Encoding.ASCII.GetString(buffer);

            Console.WriteLine(text);

            text = getBetween(text, "[", "]");
            Console.WriteLine(text);

            return text;
        }

        public string LoginSe(LoginRequest log)
        {
            int code = (int)codes.login_;
            var loginRequest = new LoginRequest
            {
                username = log.username,
                password = log.password
            };
            string jsonString = JsonSerializer.Serialize<LoginRequest>(loginRequest);
            //return jsonString;
            return helper(jsonString, code);
        }

        public string RegisterSe(SignupRequest log)
        {
            int code = (int)codes.signup_;
            var signupRequest = new SignupRequest
            {
                username = log.username,
                password = log.password,
                email = log.email
            };
            string jsonString = JsonSerializer.Serialize<SignupRequest>(signupRequest);
            //return jsonString;
            return helper(jsonString, code);
        }

        public string CreateRoomSe(CreateRoomRequest log)
        {
            int code = (int)codes.create_;
            var createRoomRequest = new CreateRoomRequest
            {
                name = log.name,
                max_users = log.max_users,
                question_count = log.question_count,
                answer_timeout = log.answer_timeout
            };
            string jsonString = JsonSerializer.Serialize<CreateRoomRequest>(createRoomRequest);
            //return jsonString;
            return helper(jsonString, code);
        }

        public string JoinRoomSe(JoinRoomRequest log)
        {
            int code = (int)codes.join_;
            var joinRoomRequest = new JoinRoomRequest
            {
                id = log.id
            };
            string jsonString = JsonSerializer.Serialize<JoinRoomRequest>(joinRoomRequest);
            //return jsonString;
            return helper(jsonString, code);
        }

        public string getPlayersAdminSe(GetPlayersInRoomRequest log)
        {
            char code = '<';
            var getPlayersInRoomRequest = new GetPlayersInRoomRequest
            {
                id = log.id
            };
            string jsonString = JsonSerializer.Serialize<GetPlayersInRoomRequest>(getPlayersInRoomRequest);
            //return jsonString;
            return helper2(jsonString, code);
        }

        public string getPlayersSe(GetPlayersInRoomRequest log)
        {
            int code = (int)codes.getPlayers_;
            var getPlayersInRoomRequest = new GetPlayersInRoomRequest
            {
                id = log.id
            };
            string jsonString = JsonSerializer.Serialize<GetPlayersInRoomRequest>(getPlayersInRoomRequest);
            //return jsonString;
            return helper(jsonString, code);
        }

        public string StatsSe()
        {          
            return "90000{}";
        }

        public string RecordsSe()
        {
            return "80000{}";
        }

        public string GetRooms()
        {
            return "60000{}";
        }

        public string LeaveRoomSe()
        {
            return "=0000{}";
        }

        public string CloseRoomSe()
        {
            return ":0000{}";
        }

        public string helper(string j, int code)
        {
            string res = "";
            res += code.ToString();
            int size = j.Length;
            res += size.ToString();
            while (res.Length < 5)
                res += 0;
            res += j;
            return res;
        }

        public string helper2(string j, char code)
        {
            string res = "";
            res += code.ToString();
            int size = j.Length;
            res += size.ToString();
            while (res.Length < 5)
                res += 0;
            res += j;
            return res;
        }
    }
}
