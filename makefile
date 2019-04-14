
SRC_DIR =./sources

OGLRENDER_DIR = $(SRC_DIR)/Render/Ogl
RENDER_SRC = $(wildcard $(OGLRENDER_DIR)/*.cpp)

OBJRENDER = $(RENDER_SRC:.cpp=.o)

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

Example: libOmgl.so libOGLRender.so
	g++ -o Example libOmgl.so main.cpp -lsfml-system -lsfml-window

libOGLRender.so: $(OBJRENDER)
	g++ -shared -o $@ $^

libOGLRender-d.so: $(OBJRENDER)
	g++ -shared -o $@ $^ -g

libOGLRender.so: libOmgl.so

libOmgl.so:
	g++ -shared -o libOmgl.so $(SRC_DIR)/Core/*.cpp $(SRC_DIR)/Debug/*.cpp $(SRC_DIR)/Exception/*.cpp $(SRC_DIR)/Model/*.cpp $(SRC_DIR)/Utils/Loader/Picture/*.cpp $(SRC_DIR)/Utils/Logger/*.cpp $(SRC_DIR)/Utils/Plugin/*.cpp $(SRC_DIR)/Utils/Reader/*.cpp -rdynamic

%.o: %.c
	g++ -o $@ -c $<

clean:
	rm -f libOGLRender.so libOmgl.so Example $(OGLRENDER_DIR)/*.o
