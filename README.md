# Relatorio do Projeto

## Autores 

- __ALAN JONATAS DE OLIVEIRA GAMA__

- __ADRIANO MELO SANTANA SOBRINHO__

- __PEDRO SAVIO SOUZA DA SILVA__

## Sobre a Entrada de dados


Basta mudar no arquivo as entradas, note que nao faz diferença a entrada de __ilha__ já que isso é irrelevante
no resultado final da ilha, por isso pusemos 99999


## Sobre as interações


- A ilha esta configurada para ser gerada aleatoriamente ( o formato e posições das coisas), assim voce precisa apertar __q__ para que o gerador de formato pare

- Use __a__ e __d__ para girar a ilha

- Use __w__ e __s__ para subir ou descer a câmera


# Especificações


- O numero de de arbustos e de coqueiro esta limitado ao numero da area ( X * Y )

- Existe um retangulo ao redor da ilha para demarcar o volume

- Os terrestres escolhem uma posição aleatoria da cena que esta preenchida com terra ( por limitação de implementação )


# Glut no windowns e mingW???

Isso foi um workaround par ausar em windowns
- g++ main.cpp -o main -lopengl32 -lglu32 -lglut32