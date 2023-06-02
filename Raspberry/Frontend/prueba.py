from kivy.app import App
from kivy.uix.gridlayout import GridLayout 
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput
from kivy.uix.boxlayout import BoxLayout

class MyBoxlayout(BoxLayout):

    pass
class MyGridlayout(GridLayout):
    pass
class NewApp(App):
    title = 'App Information Hydropower'
    def build(self):
        return MyGridlayout()
if __name__ == '__main__':
    
    NewApp().run()