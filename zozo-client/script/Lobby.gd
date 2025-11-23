extends Control

@onready var accountInput = $AccountInput
@onready var passwordInput = $PasswordInput
@onready var serverSelect = $ServerSelect

func _ready() -> void:
	serverSelect.add_item("Choose server")
	Global.lobby_socket_manager.SendServerListReq()

func _on_button_pressed() -> void:
	Global.account = accountInput.text
	Global.lobby_socket_manager.SendAuthReq(accountInput.text,passwordInput.text)
	
func _on_setting_pressed() -> void:
	Global.message_box("개발 예정...")
	
func _add_password():
	print("signaled")
	#dropDown.add_item(password)

func _add_servers(servers: Array) -> void:
	for server in servers:
		serverSelect.add_item(server)
