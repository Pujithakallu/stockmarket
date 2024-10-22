import 'dart:ui';
import 'package:flutter/material.dart';
import 'package:flutter_bloc/flutter_bloc.dart';
import 'package:book_club_app/cubit/book_cubit.dart';
import 'package:book_club_app/models/book.dart';

class BookDetail extends StatelessWidget {
  final Book book;

  const BookDetail({Key? key, required this.book}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        centerTitle: true,
        title: Text('Book Detail'),
        leading: IconButton(
          icon: Icon(Icons.arrow_back),
          onPressed: () => context.read<BookCubit>().showBookList(),
        ),
        actions: [
          Container(
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
          SizedBox(width: 16), 
        ],
      ),
      body: Container(
        color: Colors.white, 
        width: double.infinity, 
        height: MediaQuery.of(context).size.height, 
        child: Stack(
          children: [
            //  bluring the background
            BackdropFilter(
              filter: ImageFilter.blur(sigmaX: 5.0, sigmaY: 5.0),
              child: Container(
                color: Colors.grey.withOpacity(0.5), 
              ),
            ),
            SingleChildScrollView(
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  SizedBox(height: 20), 
                  Padding(
                    padding: const EdgeInsets.only(left: 16.0, right: 16.0),
                    child: Image.network(
                      book.imageUrl,
                      height: 350,
                      width: 200, 
                      fit: BoxFit.cover,
                    ),
                  ),
                  Padding(
                    padding: const EdgeInsets.all(16.0),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        Text(book.title, style: Theme.of(context).textTheme.titleLarge),
                        SizedBox(height: 20),
                        Text(book.author, style: Theme.of(context).textTheme.bodyMedium),
                        SizedBox(height: 20),
                        Text(book.description),
                      ],
                    ),
                  ),
                ],
              ),
            ),
          ],
        ),
      ),
    );
  }
}
