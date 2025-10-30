extends Control

@onready var dropDown = $CharacterDropDown

func _ready():
	dropDown.add_item("Choose your character")
	Global.socket_manager.SendCharacterListReq(Global.account, Global.token)

func _physics_process(_delta: float) -> void:
	#dropDown.add_item()
	pass

func _on_back_button_pressed() -> void:
	get_tree().change_scene_to_file("res://scene/Lobby.tscn")

func _on_select_button_pressed() -> void:
	pass # Replace with function body.
