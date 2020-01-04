
import sys, os
from PySide2.QtWidgets import QWidget, QSplitter, QTextEdit, QVBoxLayout, QPushButton, QTabWidget
from PySide2.QtWidgets import QOpenGLWidget, QApplication
from PySide2.QtGui import QOpenGLVersionProfile, QSurfaceFormat
from PySide2.QtCore import Qt

import example

class GLWidget(QOpenGLWidget):
    def __init__(self):
        super(GLWidget, self).__init__()
        self.setMouseTracking(True)
        pass

    def initializeGL(self):
        example.initGL()
        pass

    def paintGL(self):        
        example.paintGL()
        pass

    def resizeGL(self, width, height):
        example.resizeGL(width, height)
        pass

    def mouseMoveEvent(self,event):    # QMouseEvent event
        pos = "({},{})".format(event.x(),event.y())
        print( pos )

        if event.buttons() == 2:
            print( 'click' )


class Form(QWidget):
    
    def __init__(self):

        QWidget.__init__(self)
        
        self.ogl = GLWidget()

        self.tbw = QTabWidget()
        self.te_vertex = QTextEdit()
        self.te_fragment = QTextEdit()


        self.tbw.addTab( self.te_vertex, "Vertex")
        self.tbw.addTab( self.te_fragment, "Fragment")


        self.te_output = QTextEdit()
        self.te_output.setReadOnly(True)


        self.split_1 = QSplitter()
        self.split_2 = QSplitter()
        self.split_3 = QSplitter()

        self.wid_control = QWidget()
        self.vb_control = QVBoxLayout()

        self.okbt = QPushButton("Build")
        
        '''
        self.okbt.clicked.connect( lambda : example.build( self.te_vertex.toPlainText(), 
                                                           self.te_fragment.toPlainText(),))
        '''

        self.vbox = QVBoxLayout()
        self.init_widget()


    def init_widget(self):

        self.setWindowTitle("GL Editor")


        self.vb_control.addWidget(self.okbt)
        self.wid_control.setLayout(self.vb_control)

        self.split_1.setOrientation(Qt.Vertical)
        self.split_1.addWidget(self.tbw)
        self.split_1.addWidget(self.wid_control)

        self.split_2.setOrientation(Qt.Vertical)
        self.split_2.addWidget(self.ogl)
        self.split_2.addWidget(self.te_output)
        
        self.split_3.setOrientation(Qt.Horizontal)
        self.split_3.addWidget(self.split_1)
        self.split_3.addWidget(self.split_2)

        self.vbox.addWidget(self.split_3)
        self.setLayout(self.vbox)


if __name__ == "__main__":    

    app = QApplication(sys.argv)
    form = Form()
    form.show()
    exit(app.exec_())
