extends Control

@onready var accountInput = $AccountInput
@onready var passwordInput = $PasswordInput
@onready var serverSelect = $ServerSelect

func _ready() -> void:
	serverSelect.add_item("Choose server")
	GDGlobal.lobby_socket_manager.SendServerListReq()

func _on_button_pressed() -> void:
	GDGlobal.account = accountInput.text
	print("start button pressed");
	GDGlobal.lobby_socket_manager.SendAuthReq(serverSelect.get_selected_id(),accountInput.text,passwordInput.text)
	
func _on_setting_pressed() -> void:
	GDGlobal.message_box("개발 예정...")
	
func _add_password():
	print("signaled")
	#dropDown.add_item(password)

func _add_servers(servers: Dictionary[int,String]) -> void:
	for key in servers:
		serverSelect.add_item(servers[key], key)
