extends Spatial


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

var txt_server = "127.0.0.1" 
var port = 8888
var clientport = 8887
var socketUDP = PacketPeerUDP.new()
var socketUDPlisten = PacketPeerUDP.new()

func _ready():
	start_client();

func _process(delta):
	#print(socketUDP.get_available_packet_count())
	if socketUDP.get_available_packet_count() > 0:
		print(socketUDP.get_packet().get_string_from_ascii());

func start_client():

	#else:
#		printt("Listening on port: " + str(port) + " in server: " + txt_server)
	#if (socketUDP.connect_to_host(txt_server, port) != OK):
	#	print("error connecting to host")
	if (socketUDP.listen(clientport, "*", 512) != OK):
		print("Error setting destination address")
	
	#if (socketUDPlisten.wait() == OK):
	#	print("Return!")

func send(arg):
	if socketUDP.is_listening():
				socketUDP.set_dest_address(txt_server, port)
				var pac = arg.to_ascii()
				socketUDP.put_packet(pac)

func _exit_tree():
	socketUDP.close()
