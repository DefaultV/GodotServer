extends Spatial


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

var txt_server = "127.0.0.1" 
var port = 8888
var clientport = 8887
var socketUDP = PacketPeerUDP.new()
var socketUDPlisten = PacketPeerUDP.new()

enum {
	C_SPAWN = 0,
	C_TRANSFORM = 2
}

func _ready():
	start_client();
	
var DEBUG_REC = false;

func _process(delta):
	if socketUDP.get_available_packet_count() > 0:
		var rec = socketUDP.get_packet().get_string_from_ascii();
		if not DEBUG_REC:
			DEBUG_REC = true;
			print("Receiving datastream")
		#print(rec)
		if int(rec[0]) == C_SPAWN:
			#print("spawning entity..")
			spawn_entity(int(rec[2]), rec)
		if int(rec[0]) == C_TRANSFORM:
			print("Change transform");
			change_entity(int(rec[2]), rec)

var CUBE = preload("res://Cube.tscn")

func spawn_entity(id, trans):
	var entity = get_node("/root/World/Entities");
	if id == 1:
		#0 2 456789012
		#0:1:000111222
		#print("Spawning Cube " + trans.substr(4, 4))
		var cube = CUBE.instance()
		var vec:Vector3 = Vector3(float(trans.substr(4, 4)), float(trans.substr(8, 4)), float(trans.substr(12, 4)))
		var rot:Vector3 = Vector3(float(trans.substr(16, 4)), float(trans.substr(20, 4)), float(trans.substr(24, 4)))
		cube.translation = vec;
		cube.rotation = rot
		cube.scale.x = float(trans.substr(28, 4))
		cube.scale.y = float(trans.substr(32, 4))
		cube.scale.z = float(trans.substr(36, 4))
		entity.add_child(cube)

func change_entity(id, trans):
	var entity = get_node("/root/World/Entities");
	for child in entity.get_children():
		if child.ID == id:
			#0 2 456789012
			#0:1:000111222
			var vec:Vector3 = Vector3(float(trans.substr(4, 4)), float(trans.substr(8, 4)), float(trans.substr(12, 4)))
			var rot:Vector3 = Vector3(float(trans.substr(16, 4)), float(trans.substr(20, 4)), float(trans.substr(24, 4)))
			child.translation = vec;
			child.rotation = rot
			child.scale.x = float(trans.substr(28, 4))
			child.scale.y = float(trans.substr(32, 4))
			child.scale.z = float(trans.substr(36, 4))

func start_client():

	#else:
#		printt("Listening on port: " + str(port) + " in server: " + txt_server)
	#if (socketUDP.connect_to_host(txt_server, port) != OK):
	#	print("error connecting to host")
	if (socketUDP.listen(clientport, "*", 512) != OK):
		print("Error setting destination address")
	send("0")
	#if (socketUDPlisten.wait() == OK):
	#	print("Return!")

func send(arg):
	if socketUDP.is_listening():
				socketUDP.set_dest_address(txt_server, port)
				var pac = arg.to_ascii()
				socketUDP.put_packet(pac)

func _exit_tree():
	send("1");
	socketUDP.close()
