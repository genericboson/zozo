extends CharacterBody2D

const speed = 400

var accumulatedDelta = 0.0

@onready var stateAnim = $AnimatedSprite2D

func _physics_process(delta: float) -> void:
	var is_moved = false
	if Input.is_action_pressed("left"):
		position.x -= speed * delta
		stateAnim.flip_h = true
		is_moved = true
		stateAnim.play("walk_side")
	elif Input.is_action_pressed("right"):
		position.x += speed * delta
		stateAnim.flip_h = false
		is_moved = true
		stateAnim.play("walk_side")
	elif Input.is_action_just_released("left"):
		stateAnim.flip_h = true
		stateAnim.play("idle_side")
	elif Input.is_action_just_released("right"):
		stateAnim.flip_h = false
		stateAnim.play("idle_side")
		
	if Input.is_action_pressed("up"):
		position.y -= speed * delta
		is_moved = true
		stateAnim.play("walk_back")
	elif Input.is_action_pressed("down"):
		position.y += speed * delta
		is_moved = true
		stateAnim.play("walk_front")
	elif Input.is_action_just_released("up"):
		stateAnim.play("idle_back")
	elif Input.is_action_just_released("down"):
		stateAnim.play("idle_front")
		
	move_and_slide()
	
	accumulatedDelta += delta
	if GDGlobal.SECOND_PER_FRAME < accumulatedDelta:
		accumulatedDelta = 0.0
		if is_moved:
			_AfterMove(position.x, position.y)

func _AfterMove(x:float, y:float) ->void:
	GDGlobal.game_socket_manager.SendCharacterPositionUpdateReq(position.x, position.y)
	
	#region for debug position
	#var formatStr = "pos:[%f,%f]"
	#var actualStr = formatStr % [position.x,position.y]
	#print(actualStr)
	#endregion
