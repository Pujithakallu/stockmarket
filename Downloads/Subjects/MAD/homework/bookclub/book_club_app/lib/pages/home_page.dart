import 'package:flutter/material.dart';
import 'package:flutter_bloc/flutter_bloc.dart';
import '../cubit/book_cubit.dart';
import '../widgets/book_list.dart';
import '../widgets/book_detail.dart';

class HomePage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return BlocBuilder<BookCubit, BookState>(
      builder: (context, state) {
        if (state is BookListState) {
          return Scaffold(
            appBar: AppBar(
              leading: IconButton(
                icon: Icon(Icons.menu),
                onPressed: () {
                  // for menu button
                },
              ),
              title: Text('Book Club Home'),
              centerTitle: true,
              actions: [
                Padding(
                  padding: const EdgeInsets.all(8.0),
                  child: Container(
                    decoration: BoxDecoration(
                      shape: BoxShape.circle,
                      border: Border.all(color: Colors.black, width: 2),
                    ),
                    child: CircleAvatar(
                      radius: 10,
                      child: Icon(
                        Icons.person,
                        color: Colors.black,
                        size: 15,
                      ),
                    ),
                  ),
                ),
              ],
            ),
            body: Column(
              children: [
                Padding(
                  padding: const EdgeInsets.all(16.0),
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Row(
                        mainAxisAlignment: MainAxisAlignment.start,
                        children: [
                          Text(
                            'Sort by',
                            style: Theme.of(context).textTheme.titleMedium,
                          ),
                          SizedBox(width: 16.0),
                          Container(
                            padding: const EdgeInsets.symmetric(horizontal: 10.0, vertical: 4.0),
                            decoration: BoxDecoration(
                              border: Border.all(color: Colors.grey),
                              borderRadius: BorderRadius.circular(8.0),
                              color: state.sortBy == SortBy.author ? Color(0xFFFEF7FF) : Colors.white,
                            ),
                            child: GestureDetector(
                              onTap: () {
                                if (state.sortBy != SortBy.author) {
                                  context.read<BookCubit>().toggleSort();
                                }
                              },
                              child: Text(
                                'Author',
                                style: TextStyle(
                                  color: state.sortBy == SortBy.author ? Colors.black : Colors.black,
                                ),
                              ),
                            ),
                          ),
                          SizedBox(width: 8.0),
                          Container(
                            padding: const EdgeInsets.symmetric(horizontal: 15.0, vertical: 4.0),
                            decoration: BoxDecoration(
                              border: Border.all(color: Colors.grey),
                              borderRadius: BorderRadius.circular(8.0),
                              color: state.sortBy == SortBy.title ? Color(0xFFFEF7FF) : Colors.white,
                            ),
                            child: GestureDetector(
                              onTap: () {
                                if (state.sortBy != SortBy.title) {
                                  context.read<BookCubit>().toggleSort();
                                }
                              },
                              child: Text(
                                'Title',
                                style: TextStyle(
                                  color: state.sortBy == SortBy.title ? Colors.black : Colors.black,
                                ),
                              ),
                            ),
                          ),
                        ],
                      ),
                      /*SizedBox(height: 8.0),
                      Text(
                        'Books',
                        style: Theme.of(context).textTheme.titleLarge?.copyWith(fontWeight: FontWeight.bold),
                      ),*/
                    ],
                  ),
                ),
                Expanded(
                  child: BookList(books: state.books),
                ),
              ],
            ),
          );
        } else if (state is BookDetailState) {
          return BookDetail(book: state.book);
        }
        return Center(child: CircularProgressIndicator());
      },
    );
  }
}
