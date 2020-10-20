extends Camera


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

var network;
# Called when the node enters the scene tree for the first time.
func _ready():
	network = get_node("/root/World/Network");
	#Input.MOUSE_MODE_HIDDEN
	Input.MOUSE_MODE_CAPTURED


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _input(event):
   # Mouse in viewport coordinates.
	if event is InputEventMouseButton:
		if event.pressed:
			network.send("0Hello from Godot!");
	elif event is InputEventMouseMotion:
		get_parent().rotate_y(-event.relative.x * 0.01);
		rotate_x(-event.relative.y * 0.01)
