extends CharacterBody2D

const speed = 400

@onready var stateAnim = $AnimatedSprite2D
@onready var my_csharp_node = load("res://script/SocketManager.cs").new()

func _physics_process(delta: float) -> void:
	if Input.is_action_pressed("left"):
		position.x -= speed * delta
		stateAnim.flip_h = true
		stateAnim.play("walk_side")
	elif Input.is_action_pressed("right"):
		position.x += speed * delta
		stateAnim.flip_h = false
		stateAnim.play("walk_side")
	elif Input.is_action_just_released("left"):
		stateAnim.flip_h = true
		stateAnim.play("idle_side")
	elif Input.is_action_just_released("right"):
		stateAnim.flip_h = false
		stateAnim.play("idle_side")
		
	if Input.is_action_pressed("up"):
		position.y -= speed * delta
		stateAnim.play("walk_back")
	elif Input.is_action_pressed("down"):
		position.y += speed * delta
		stateAnim.play("walk_front")
	elif Input.is_action_just_released("up"):
		stateAnim.play("idle_back")
	elif Input.is_action_just_released("down"):
		stateAnim.play("idle_front")
		
	my_csharp_node.Test()
		
	move_and_slide()
