extends RigidBody

export var speed = 0.1;
export var rot_speed = 0.85;
export var max_velocity = 0.4;
export var mouse_sensitivity = Vector2(0.002, 0.003);

var velocity = Vector3.ZERO
var anchor;
var camera;
# Called when the node enters the scene tree for the first time.
func _ready():
	anchor = get_node("Camera_anchor");
	camera = get_node("Camera_anchor/Camera");
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED);


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta):
	get_input(delta)
	if (velocity.length() >= max_velocity):
		apply_central_impulse(velocity.normalized() * max_velocity);
	else:
		apply_central_impulse(velocity);

func get_input(delta):
	var vy = velocity.y
	velocity = Vector3.ZERO
	if Input.is_action_pressed("w"):
		velocity += -anchor.transform.basis.z * speed;
	if Input.is_action_pressed("s"):
		velocity += anchor.transform.basis.z * speed;
	if Input.is_action_pressed("d"):
		velocity += anchor.transform.basis.x * speed;
	if Input.is_action_pressed("a"):
		velocity += -anchor.transform.basis.x * speed;
	velocity.y = vy

func _input(event):
	if event is InputEventMouseMotion:
		anchor.rotate_y(-event.get_relative().x * mouse_sensitivity.x)
		var camrotatey = -event.get_relative().y * mouse_sensitivity.y;
		if (camera.rotation.x + camrotatey < 1.5 and camera.rotation.x + camrotatey > -1): #Radians
			camera.rotate_x(camrotatey);
