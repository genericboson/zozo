extends Control

@onready var accountInput = $AccountInput
@onready var passwordInput = $PasswordInput

@onready var dropDown = $CharacterDropDown

func _ready():
	var global_emitter = get_node("/root/Global")
	if global_emitter:
		global_emitter.connect("InsertToCharacterListDropdown",_on_insert_to_dropdown);
	else:
		print("signal connect error")

func _on_button_pressed() -> void:
	print("button pressed")
	
	Global.socket_manager.SendLogin(accountInput.text,passwordInput.text)
	
	#get_tree().change_scene_to_file("res://scene/CharacterSelect.tscn")

func _on_setting_pressed() -> void:
	Global.message_box("개발 예정...")

func _on_insert_to_dropdown(characterName: String) -> void:
	dropDown.add_item(characterName)
